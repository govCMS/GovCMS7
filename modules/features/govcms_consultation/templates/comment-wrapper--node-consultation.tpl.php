<?php
/**
 * @file
 * Default theme implementation for comments.
 */
?>
<div id="disqus_thread" class="consultation__disqus"></div>
<script type="text/javascript">
  /* * * CONFIGURATION VARIABLES * * */
  var disqus_shortname = '<?php print check_plain(variable_get('consultation_disqus_account')); ?>';
  var disqus_identifier = 'node/<?php print $node->nid; ?>';
  var disqus_url = '<?php global $base_url; print $base_url . "/node/" . $node->nid; ?>';

  /* * * DON'T EDIT BELOW THIS LINE * * */
  (function() {
    var dsq = document.createElement('script'); dsq.type = 'text/javascript'; dsq.async = true;
    dsq.src = '//' + disqus_shortname + '.disqus.com/embed.js';
    (document.getElementsByTagName('head')[0] || document.getElementsByTagName('body')[0]).appendChild(dsq);
  })();
</script>
<noscript>Please enable JavaScript to view the <a href="https://disqus.com/?ref_noscript" rel="nofollow">comments powered by Disqus.</a></noscript>
