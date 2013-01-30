<?php
/**
 * @file
 * agov_content_promotion.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function agov_content_promotion_content_defaults() {
  $content = array();

  $content['agov_promotion_1'] = (object) array(
    'exported_path' => 'promotions/nam-eget-placerat-sapien',
    'title' => 'Nam eget placerat sapien',
    'status' => '1',
    'promote' => '1',
    'sticky' => '0',
    'type' => 'footer_teaser',
    'language' => 'und',
    'created' => '1345178112',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'agov_promotion_1',
    'field_description' => array(
      'und' => array(
        0 => array(
          'value' => '<p>Sed gravida, dui et sodales auctor, lacus massa ultrices neque, ut venenatis odio nisi vitae dolor. Mauris eu dui purus, non consectetur ipsum. Donec quis nisi ante, egestas egestas urna. Nam eget placerat sapien. Sed a metus vel felis sodales scelerisque. Morbi molestie rutrum justo, non tincidunt lectus tincidunt a. Vestibulum et auctor tortor.</p>',
          'format' => 'rich_text',
          'safe_value' => ' <p>Sed gravida, dui et sodales auctor, lacus massa ultrices neque, ut venenatis odio nisi vitae dolor. Mauris eu dui purus, non consectetur ipsum. Donec quis nisi ante, egestas egestas urna. Nam eget placerat sapien. Sed a metus vel felis sodales scelerisque. Morbi molestie rutrum justo, non tincidunt lectus tincidunt a. Vestibulum et auctor tortor.</p> ',
        ),
      ),
    ),
    'field_image' => array(
      'und' => array(
        0 => array(
          'alt' => 'Testing promotion alt text 1',
          'title' => 'Testing promotion title text 1',
          'width' => '78',
          'height' => '52',
          'filename' => 'bigstock-Koala-3496163.jpg',
          'uri' => 'public://bigstock-Koala-3496163.jpg',
          'filemime' => 'image/jpeg',
          'filesize' => '1923',
          'status' => '1',
          'type' => 'image',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image_dimensions' => array(
            'width' => '78',
            'height' => '52',
          ),
          'image' => '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',
        ),
      ),
    ),
    'field_reference' => array(
      'und' => array(
        0 => array(
          'machine_name' => 'agov_publication_4',
        ),
      ),
    ),
    'field_tags' => array(
      'und' => array(
        0 => array(
          'tid' => '1',
        ),
        1 => array(
          'tid' => '4',
        ),
      ),
    ),
  );

  $content['agov_promotion_2'] = (object) array(
    'exported_path' => 'promotions/suspendisse-id-elit-arcu',
    'title' => 'Suspendisse id elit arcu.',
    'status' => '1',
    'promote' => '1',
    'sticky' => '0',
    'type' => 'footer_teaser',
    'language' => 'und',
    'created' => '1345178212',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'agov_promotion_2',
    'field_description' => array(
      'und' => array(
        0 => array(
          'value' => '<p>Nullam tristique adipiscing mauris sit amet pharetra. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Aliquam non mauris diam, et vehicula neque. Quisque sit amet libero sapien. Vestibulum bibendum metus at nisl tempus in viverra ante porttitor. Sed nulla odio, aliquam in aliquam a, dictum sit amet sapien. Maecenas ac malesuada magna.</p>
',
          'format' => 'rich_text',
          'safe_value' => ' <p>Nullam tristique adipiscing mauris sit amet pharetra. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Aliquam non mauris diam, et vehicula neque. Quisque sit amet libero sapien. Vestibulum bibendum metus at nisl tempus in viverra ante porttitor. Sed nulla odio, aliquam in aliquam a, dictum sit amet sapien. Maecenas ac malesuada magna.</p> ',
        ),
      ),
    ),
    'field_image' => array(
      'und' => array(
        0 => array(
          'alt' => 'Testing promotion alt text 2',
          'title' => 'Testing promotion title text 2',
          'width' => '78',
          'height' => '52',
          'filename' => 'bigstock-A-traffic-jam-with-rows-of-car-24706940.jpg',
          'uri' => 'public://bigstock-A-traffic-jam-with-rows-of-car-24706940.jpg',
          'filemime' => 'image/jpeg',
          'filesize' => '2175',
          'status' => '1',
          'type' => 'image',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image_dimensions' => array(
            'width' => '78',
            'height' => '52',
          ),
          'image' => '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',
        ),
      ),
    ),
    'field_reference' => array(
      'und' => array(
        0 => array(
          'machine_name' => 'agov_publication_8',
        ),
      ),
    ),
    'field_tags' => array(
      'und' => array(
        0 => array(
          'tid' => '7',
        ),
      ),
    ),
  );

  $content['agov_promotion_3'] = (object) array(
    'exported_path' => 'promotions/integer-lacinia-ullamcorper-tempor',
    'title' => 'Integer lacinia ullamcorper tempor',
    'status' => '1',
    'promote' => '1',
    'sticky' => '0',
    'type' => 'footer_teaser',
    'language' => 'und',
    'created' => '1345178302',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'agov_promotion_3',
    'field_description' => array(
      'und' => array(
        0 => array(
          'value' => '<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin congue vulputate convallis. Nullam auctor, turpis ut faucibus dapibus, dui enim fermentum neque, ut elementum felis augue sed turpis. Ut ac nunc ut libero imperdiet adipiscing. Mauris eu dolor ac diam commodo imperdiet id a lectus. Nam et ante ac neque scelerisque porttitor. In eu erat turpis, non consequat elit. Vivamus molestie enim vitae massa eleifend blandit. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Morbi dictum velit et erat luctus tincidunt. Ut eget tellus nisi, feugiat malesuada nibh. Etiam at est purus, at gravida lacus.</p>',
          'format' => 'rich_text',
          'safe_value' => ' <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin congue vulputate convallis. Nullam auctor, turpis ut faucibus dapibus, dui enim fermentum neque, ut elementum felis augue sed turpis. Ut ac nunc ut libero imperdiet adipiscing. Mauris eu dolor ac diam commodo imperdiet id a lectus. Nam et ante ac neque scelerisque porttitor. In eu erat turpis, non consequat elit. Vivamus molestie enim vitae massa eleifend blandit. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Morbi dictum velit et erat luctus tincidunt. Ut eget tellus nisi, feugiat malesuada nibh. Etiam at est purus, at gravida lacus.</p> ',
        ),
      ),
    ),
    'field_image' => array(
      'und' => array(
        0 => array(
          'alt' => 'Testing promotion alt text 3',
          'title' => 'Testing promotion title text 3',
          'width' => '64',
          'height' => '64',
          'filename' => '29154_1449985617556_2658441_n.jpeg',
          'uri' => 'public://29154_1449985617556_2658441_n.jpeg',
          'filemime' => 'image/jpeg',
          'filesize' => '1790',
          'status' => '1',
          'type' => 'image',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image_dimensions' => array(
            'width' => '64',
            'height' => '64',
          ),
          'image' => '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',
        ),
      ),
    ),
    'field_reference' => array(
      'und' => array(
        0 => array(
          'machine_name' => 'agov_publication_3',
        ),
      ),
    ),
    'field_tags' => array(
      'und' => array(
        0 => array(
          'tid' => '3',
        ),
      ),
    ),
  );

return $content;
}
