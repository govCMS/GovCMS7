
jQuery(document).ready(function($) {

  var default_weights = Drupal.settings.crumbs.default_weights;

  function hashInteger(str, range) {
    str = Drupal.settings.crumbs.keys_md5[str];
    if (0 === str.length) {
      return 0;
    }
    var hash = 0, i, c;
    for (i = 0; i < str.length; i++) {
      c  = str.charCodeAt(i);
      hash  = ((hash << 5) - hash) + c;
      hash |= 0; // Convert to 32bit integer
    }
    return Math.abs(hash) % range;
  }

  function TableTreeWidget() {

    var rows = {};

    /**
     * Set a row value.
     */
    function rowSetValue(key, value) {
      var row = rows[key];

      row.value = value;

      var hadExplicitValue = row.hasExplicitValue;
      row.hasExplicitValue = (value >= 0 || 'disabled' === value);

      if (hadExplicitValue === row.hasExplicitValue) {
        // Nothing has changed.
        rowCheckVisibility(key);
        return;
      }

      rowCheckExplicity(key);
      rowCheckInheritFromKey(key);
    }

    /**
     * A user did click the +/- icon to expand or collapse the subtree.
     */
    function rowToggleManuallyExpanded(key) {
      var row = rows[key];
      row.isManuallyExpanded = !row.isManuallyExpanded;

      rowCheckExpandIcon(key);
      rowCheckChildrenVisibility(key);
    }

    /**
     * Some values have changed that might change the inExpandedTrail value.
     */
    function rowCheckChildrenVisibility(key) {
      var row = rows[key]
        , kChild
        ;

      for (kChild in row.children) {
        rowCheckVisibility(kChild);
      }
    }

    /**
     * Some explicity stuff may have changed so the widget must get updated.
     */
    function rowCheckInheritFromKey(key) {
      var row = rows[key];
      var currentInheritFromKey = row.inheritFromKey;

      if (row.hasExplicitValue) {
        row.inheritFromKey = null;
      }
      else if (row.hasDefaultValue) {
        row.inheritFromKey = '.defaultValue';
      }
      else if (!row.parent) {
        row.inheritFromKey = '.*';
      }
      else if (row.parent.inheritFromKey === null) {
        row.inheritFromKey = row.parentKey;
      }
      else {
        row.inheritFromKey = row.parent.inheritFromKey;
      }

      if (currentInheritFromKey === row.inheritFromKey) {
        // Nothing has changed.
        return;
      }

      // Check children
      for (var kChild in row.children) {
        rowCheckInheritFromKey(kChild);
      }
    }

    /**
     * Some values on a row have changed, which might change the isExplicit value.
     */
    function rowCheckExplicity(key) {
      var row = rows[key];

      // Check if explicity has changed.
      var wasExplicit = row.isExplicit;
      row.isExplicit = row.hasExplicitValue || row.hasDefaultValue || (row.nExplicitChildren > 0);

      if (wasExplicit === row.isExplicit) {
        // No change.
        return;
      }

      // Check visibility.
      rowCheckVisibility(key);

      // Check expand +/- icon.
      rowCheckExpandIcon(key);

      // Check parent.
      if (row.parent) {
        if (row.isExplicit) {
          ++row.parent.nExplicitChildren;
        }
        else if (wasExplicit) {
          --row.parent.nExplicitChildren;
        }
        rowCheckExplicity(row.parentKey);

        // Icon may have changed.
        rowCheckExpandIcon(row.parentKey);
      }
    }

    /**
     * Some values have changed, which might change the +/- icon.
     */
    function rowCheckExpandIcon(key) {
      var row = rows[key];
      if (row.depth === 0) {
        row.$button.html('#');
      }
      else if (row.nChildren === 0) {
        row.$button.html('=');
      }
      else if (row.nExplicitChildren === row.nChildren) {
        row.$button.html('~');
      }
      else if (row.isManuallyExpanded) {
        row.$button.html('-');
      }
      else {
        row.$button.html('+');
      }
    }

    /**
     * Some values on a row have changed, which might change the isVisible value.
     */
    function rowCheckVisibility(key) {
      var row = rows[key];
      var wasVisible = row.isVisible;
      row.isVisible = 0
        || !row.parent
        || (row.parent.isVisible && row.parent.isManuallyExpanded)
        || row.isExplicit
        || (row.originalValue !== row.value)
      ;

      if (wasVisible === row.isVisible) {
        // No change.
        return;
      }

      if (row.isVisible) {
        row.$tr.removeClass('collapsed');
      }
      else {
        row.$tr.addClass('collapsed');
      }

      rowCheckChildrenVisibility(key);
    }

    this.addRowWidget = function(key, $tr, rowWidget) {
      var parts = key.split('.')
        , depth = parts.length
        , name = parts.pop()
        , row
        ;
      if ('*' === name) {
        --depth;
        if (0 !== depth) {
          name = parts.pop() + '.*';
        }
      }
      var $tdFirst = $('td:first-child', $tr);
      var $label = $('<div class="crumbs-admin-row-label">').css('margin-left', (20 * depth) + 'px');
      $('<span class="rowText">').html(key).appendTo($label);
      var $button = $('<div class="crumbs-admin-expand-icon">').html('+').prependTo($label);
      $tdFirst.html('').append($label);
      var parentKeys = [];
      var parentKey = false;
      if (depth > 0) {
        parentKeys.push('*');
        if (depth > 1) {
          parentKey = parts[0];
          for (var i = 1; true; ++i) {
            parentKeys.push(parentKey + '.*');
            if (i >= parts.length) {
              break;
            }
            parentKey += '.' + parts[i];
          }
          parentKey += '.*';
        }
        else {
          parentKey = '*';
        }
        rows[parentKey].children[key] = true;
        ++rows[parentKey].nChildren;
      }

      row = {
        $tr: $tr,
        $button: $button,
        parentKeys: parentKeys,
        parentKey: parentKey,
        parent: rows[parentKey],
        depth: depth,
        children: {},
        nChildren: 0,
        isManuallyExpanded: (depth < 1),
        // inExpandedTrail: (depth < 1),
        nExplicitChildren: 0,
        isExplicit: null,
        hasExplicitValue: null,
        hasDefaultValue: null,
        rowWidget: rowWidget,
        _: '_'
      };

      rows[key] = row;
    };

    this.init = function(values) {
      for (var key in rows) {
        (function(key, row, value){
          if (row.depth === 0) {
            // Root item cannot be collapsed.
          }
          else if (!row.nChildren) {
            // Leafs cannot be collapsed or expanded.
          }
          else {
            // Other items can be collapsed and expanded.
            row.$button.click(function(){
              rowToggleManuallyExpanded(key);
            });
          }
          row.originalValue = value;
          row.value = value;
          if (undefined !== default_weights[key]) {
            row.hasDefaultValue = true;
          }
          rowSetValue(key, value);
          rowCheckExplicity(key);
          rowCheckInheritFromKey(key);
          rowCheckVisibility(key);
          rowCheckExpandIcon(key);
        })(key, rows[key], values[key]);
      }
    };

    /**
     * Set a row value.
     */
    this.setValues = function(values) {
      for (var key in values) {
        rowSetValue(key, values[key]);
      }
    };
  }

  function determineParentKeys(key) {
    if ('*' === key || '' === key) {
      return [];
    }
    var fragments = key.split('.');
    if ('*' === fragments.pop()) {
      fragments.pop();
    }
    var parents = ['*'];
    var parentBase = '';
    for (var i = 0; i < fragments.length; ++i) {
      parentBase += fragments[i] + '.';
      parents.push(parentBase + '*');
    }
    return parents.reverse();
  }

  function RowWidget($tdInput, rowKey, tellOthers) {

    var defaultBoxes = {
      'disabled': $('<div class="default-box crumbs-admin-slider-box">')
    };

    var $tr = $tdInput.parent();
    $tdInput.hide();
    var $td = $tdInput;

    var $tdAuto = $td = $('<td>').insertAfter($td);
    var $auto = $('<div class="state-auto state">').appendTo($tdAuto);

    var $tdDisabled = $td = $('<td>').insertAfter($td);
    var $disabled = $('<div class="state-disabled state">').appendTo($tdDisabled);

    var $tdEnabled = $td = $('<td>').insertAfter($td);
    var $enabled = $('<div class="state-enabled state">').appendTo($tdEnabled);

    if ('*' === rowKey) {
      $auto.hide();
      $disabled.hide();
    }

    var rowParentKeys = determineParentKeys(rowKey);

    var currentQueue;
    var currentValues;
    var boxes = {};
    var $rowKeyBox;
    var effectiveKey;
    var effectiveValue;
    // $tdInput.hide();

    // Set slider value if someone clicks.
    $disabled.click(function(){
      tellOthers('disabled');
    });

    $auto.click(function(){
      tellOthers('auto');
    });

    $enabled.click(function(event){
      for (var k in boxes) {
        if (event.srcElement === boxes[k][0]) {
          if (currentValues[rowKey] >= 0) {
            // Element already enabled.
            if (currentValues[rowKey] === currentValues[k]) {
              // tellOthers('auto');
            }
            else {
              tellOthers(currentValues[k]);
            }
          }
          else {
            // Element was 'disabled' or 'auto' before.
            if (event.offsetX <= 10) {
              tellOthers(currentValues[k]);
            }
            else {
              tellOthers(currentValues[k]);
            }
          }
          return;
        }
      }
    });

    /**
     * Values have changed.
     */
    function checkSliderWidth() {

      if (currentValues[rowKey] >= 0) {
        $enabled.css({'width': (20 * currentQueue.length) + 'px', 'margin-left': '10px', 'padding-left': '0'});
      }
      else {
        $enabled.css({'width': (20 * currentQueue.length + 20) + 'px', 'margin-left': '0', 'padding-left': '10px'});
      }
    }

    function checkRowValue() {
      var rowValue = currentValues[rowKey];
      effectiveKey = rowKey;
      effectiveValue = rowValue;

      // Clean up the disabled and auto element.
      $disabled.children().remove();
      $auto.children().remove();

      if (rowValue >= 0) {
        // Explicit user-specified value in the "enabled" section.
        return;
      }

      if ('disabled' === rowValue) {
        // Explicit user-specified "disabled" value.
        $disabled.append(boxes[rowKey]);
        return;
      }

      $auto.append(boxes[rowKey]);

      if (undefined !== default_weights[rowKey]) {
        // Default value.
        effectiveValue = 'disabled';
        $disabled.append(defaultBoxes['disabled']);
        return;
      }

      // Inherited value.
      var parentKey
        , parentValue
        , $parentBox
        , parentFound = false
        ;

      // Determine the correct parent to inherit from.
      for (var i = 0; i < rowParentKeys.length; ++i) {

        parentKey = rowParentKeys[i];
        parentValue = currentValues[parentKey];
        $parentBox = boxes[parentKey];

        if (0
          || parentFound
          || (1
            && !(parentValue >= 0)
            && 'disabled' !== parentValue
            && undefined === default_weights[parentKey]
          )
        ) {
          $parentBox.removeClass('inheritFromHere');
          continue;
        }

        $parentBox.addClass('inheritFromHere');
        parentFound = true;
        effectiveKey = parentKey;
        if (parentValue >= 0) {
          effectiveValue = parentValue;
        }
        else if ('disabled' === parentValue) {
          $disabled.append($parentBox);
          effectiveValue = 'disabled';
        }
        else if (undefined === default_weights[parentKey]) {
          $disabled.append($parentBox);
          effectiveValue = 'disabled';
        }
      }

      if (!parentFound) {
        throw 'No inherited value found for key "' + rowKey + '".';
      }
    }

    function checkQueueClasses() {
      for (var k in boxes) {
        var $box = boxes[k];
        var v = currentValues[k];
        if (0
          || k === effectiveKey
          || !(effectiveValue >= 0)
          || !(v >= 0)
        ) {
          $box.removeClass('afterEffectiveBox');
          $box.removeClass('beforeEffectiveBox');
        }
        else if (v < effectiveValue) {
          $box.removeClass('afterEffectiveBox');
          $box.addClass('beforeEffectiveBox');
        }
        else {
          $box.addClass('afterEffectiveBox');
          $box.removeClass('beforeEffectiveBox');
        }
      }
    }

    function checkRowClasses() {

      $tr.removeClass('effectivelyEnabled');
      $tr.removeClass('effectivelyDisabled');
      $tr.removeClass('explicitlyDisabled');
      $tr.removeClass('explicitlyEnabled');
      $tr.removeClass('hasExplicitValue');
      $tr.removeClass('useDefaultValue');
      $tr.removeClass('inheritValue');

      if (effectiveValue >= 0) {
        $tr.addClass('effectivelyEnabled');
      }
      else {
        $tr.addClass('effectivelyDisabled');
      }

      if (rowKey === effectiveKey) {
        $tr.addClass('hasExplicitValue');
        if (currentValues[rowKey] >= 0) {
          $tr.addClass('explicitlyEnabled');
        }
        else {
          $tr.addClass('explicitlyDisabled');
        }
      }
      else if ('.defaultValue' === effectiveKey) {
        $tr.addClass('useDefaultValue');
      }
      else {
        $tr.addClass('inheritValue');
      }
    }

    /**
     * Initialize
     */
    this.init = function(values, queue) {

      currentValues = values;
      currentQueue = queue;

      var $box, k;

      // Create boxes.
      for (k in values) {
        $box = $('<div class="crumbs-admin-slider-box">');
        if (k === '*') {
          $box.css('background-position', 'left top');
        }
        else {
          var hashIndex = hashInteger(k, 6) + 1;
          $box.css('background-position', 'left ' + (hashIndex * -30) + 'px');
        }
        $box.attr('title', k);
        boxes[k] = $box;
      }
      boxes[rowKey].addClass('activeBox');
      $rowKeyBox = boxes[rowKey];

      // Build queue of enabled boxes.
      for (var i = 0; i < queue.length; ++i) {
        k = queue[i];
        $box = boxes[k];
        $enabled.append($box);
      }

      checkSliderWidth();
      checkRowValue();
      checkQueueClasses();
      checkRowClasses();
    };

    /**
     * Element has a new weight.
     */
    this.move = function(key, oldWeight, newWeight, queue, values) {
      var $boxToMove = boxes[key];
      if (newWeight >= 0) {
        if (!currentQueue[newWeight]) {
          console.log('PROBLEM', newWeight, currentQueue);
        }
        var targetKey = currentQueue[newWeight];
        var $targetBox = boxes[targetKey];
      }
      if (oldWeight >= 0 && newWeight >= 0) {
        if (oldWeight < newWeight) {
          // Increase weight
          $targetBox.after($boxToMove);
        }
        else if (oldWeight > newWeight) {
          // Decrease weight
          $targetBox.before($boxToMove);
        }
        else {
          // Weight stays the same.
        }
      }
      else if (newWeight >= 0) {
        // Enable the box.
        $targetBox.before($boxToMove);
      }
      else if (oldWeight >= 0) {
        // Disable the box.
        $boxToMove.remove();
      }
      else {
        // Box remains disabled.
      }
      currentQueue = queue;
      currentValues = values;
      $enabled.css({'width': (20 * queue.length + 20) + 'px', 'margin-left': '0', 'padding-left': '10px'});

      checkSliderWidth();
      checkRowValue();
      checkQueueClasses();
      checkRowClasses();
    };
  }

  function TableWidget($table, tableTreeWidget) {

    var values = {};
    var queue = [];
    var widgets = {};
    var inputs = {};
    var depths = {};

    var $thead = $('<thead>').prependTo($table);
    var $trHead = $('<tr>').prependTo($thead);
    var headCaptions = [
      'Plugin name',
      'Auto',
      'Disabled',
      'Enabled, with weight',
      'Method',
      'Route',
      'Description'
    ];
    for (var i = 0; i < headCaptions.length; ++i) {
      $('<th>').html(headCaptions[i]).appendTo($trHead);
    }

    /**
     * Normalize the values variable.
     */
    function normalize() {
      var k, i;
      queue = [];
      for (k in values) {
        if (!isNaN(parseFloat(values[k]))) {
          queue.push(k);
        }
        else if ('disabled' !== values[k]) {
          values[k] = 'auto';
        }
      }
      queue.sort(function(k0, k1) {
        return values[k0] - values[k1];
      });
      for (i = 0; i < queue.length; ++i) {
        values[queue[i]] = i;
      }
    }

    /**
     * Update all sliders.
     */
    function updateInputs() {
      for (var k in values) {
        inputs[k].val(values[k]);
      }
    }

    this.setWeight = function(key, value) {
      if (!(value >= 0) && key === '*') {
        // Illegal.
        return;
      }
      if (values[key] !== value) {
        var oldValue = values[key];
        values[key] = value;
        if (value >= 0) {
          if (value > oldValue) {
            values[key] += 0.5;
          }
          else {
            values[key] -= 0.5;
          }
        }
        normalize();
        updateInputs();
        for (var k in widgets) {
          widgets[k].move(key, oldValue, values[key], queue, values);
        }
        tableTreeWidget.setValues(values);
      }
    };

    this.addWeightWidget = function(key, weightWidget, $input) {
      widgets[key] = weightWidget;
      inputs[key] = $input;
    };

    this.init = function() {
      var v, k;
      for (k in inputs) {
        v = inputs[k].val();
        values[k] = v;
        var depth = k.split('.').length;
        if ('*' === k[k.length - 1]) {
          --depth;
        }
        depths[k] = depth;
      }
      if (!(values['*'] >= 0)) {
        values['*'] = 0;
      }
      normalize();
      for (k in inputs) {
        widgets[k].init(values, queue);
      }
      updateInputs();
      tableTreeWidget.init(values);
    };
  }

  function setDepthColor($tr, key) {
    var depth = key.split('.').length;
    if ('*' === key[key.length - 1]) {
      --depth;
    }
    // Determine a color.
    var lum = Math.round(255 * Math.pow(0.97, depth));
    var rgba = [lum, lum, lum, 1];
    var color = 'rgba(' + rgba.join(',') + ')';
    $tr.css('background-color', color);
  }

  $('table#crumbs_weights_expansible').each(function(){
    var $table = $(this);
    var tableTreeWidget = new TableTreeWidget();
    var tableWidget = new TableWidget($table, tableTreeWidget);
    $('input.form-text', $table).each(function(){
      var $input = $(this);
      var $td = $input.parent().parent();
      var $tr = $td.parent();
      var key = $input.attr('name').substr('crumbs_weights['.length);
      key = key.substr(0, key.length -1);
      setDepthColor($tr, key);
      var weightWidget = new RowWidget($td, key, function(value){
        $input.val(value);
        tableWidget.setWeight(key, value);
      });
      tableTreeWidget.addRowWidget(key, $tr, weightWidget);
      tableWidget.addWeightWidget(key, weightWidget, $input);
    });
    tableWidget.init();
  });
});
