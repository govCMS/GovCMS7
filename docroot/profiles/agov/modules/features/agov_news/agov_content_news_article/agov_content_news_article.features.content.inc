<?php
/**
 * @file
 * agov_content_news_article.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function agov_content_news_article_content_defaults() {
  $content = array();

  $content['agov_news_article_1'] = (object) array(
    'exported_path' => 'news-media/news/duis-tincidunt-ultricies-congue',
    'title' => 'Duis tincidunt ultricies congue.',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'news_article',
    'language' => 'und',
    'created' => 1374467205,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'agov_news_article_1',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean tortor turpis, porttitor at aliquam sed, pulvinar quis lacus. In hac habitasse platea dictumst. Suspendisse rhoncus urna quis nunc tristique faucibus. Aliquam erat volutpat. In eget nunc eget arcu eleifend fermentum. Aenean hendrerit, metus ut facilisis egestas, metus lacus viverra magna, id ultricies ante arcu pellentesque diam. Maecenas aliquet risus nec purus malesuada euismod. Sed venenatis tincidunt felis, sed tristique velit imperdiet vitae. Duis elit est, dapibus et consequat sed, porta et enim. Fusce condimentum, tellus ac molestie ullamcorper, neque libero laoreet felis, in ultricies felis nibh ac purus. Curabitur sollicitudin risus ut diam ultricies tempor. Curabitur placerat nunc sed velit tempus ut pulvinar odio feugiat.</p>
<p>Vivamus risus erat, fermentum fermentum mattis ut, eleifend vel enim. Duis tincidunt ultricies congue. Mauris vitae felis quis nibh ultrices vulputate. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Mauris eu quam turpis, vitae blandit enim. In eget dolor nulla, ac vehicula libero. Nunc eget ante elementum velit pretium euismod. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus.</p>
<p>Fusce tortor elit, fringilla vitae hendrerit vel, consequat ut lectus. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Suspendisse potenti. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam laoreet, lectus et ultrices aliquet, metus arcu pretium ipsum, vitae faucibus nibh turpis id elit. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed massa libero, fermentum quis tincidunt dignissim, blandit sit amet tellus. Nam feugiat mauris sit amet tortor venenatis tristique.</p>
<p>Nulla auctor imperdiet nibh, nec bibendum magna rutrum a. Aliquam quis eros augue. Cras mauris enim, feugiat sagittis suscipit non, cursus et ligula. Vivamus eu nisi eros. Mauris odio tellus, venenatis ac lobortis sed, cursus quis ligula. Nam felis nisi, blandit ultrices scelerisque quis, blandit at nisi. Nullam at ligula ipsum, a placerat orci. Vivamus urna lacus, bibendum ut commodo vehicula, volutpat et dui. Cras commodo feugiat aliquam.</p>',
          'summary' => 'Vivamus risus erat, fermentum fermentum mattis ut, eleifend vel enim. Duis tincidunt ultricies congue. Mauris vitae felis quis nibh ultrices vulputate. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Mauris eu quam turpis, vitae blandit enim. In eget dolor nulla, ac vehicula libero. ',
          'format' => 'rich_text',
          'safe_value' => '<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean tortor turpis, porttitor at aliquam sed, pulvinar quis lacus. In hac habitasse platea dictumst. Suspendisse rhoncus urna quis nunc tristique faucibus. Aliquam erat volutpat. In eget nunc eget arcu eleifend fermentum. Aenean hendrerit, metus ut facilisis egestas, metus lacus viverra magna, id ultricies ante arcu pellentesque diam. Maecenas aliquet risus nec purus malesuada euismod. Sed venenatis tincidunt felis, sed tristique velit imperdiet vitae. Duis elit est, dapibus et consequat sed, porta et enim. Fusce condimentum, tellus ac molestie ullamcorper, neque libero laoreet felis, in ultricies felis nibh ac purus. Curabitur sollicitudin risus ut diam ultricies tempor. Curabitur placerat nunc sed velit tempus ut pulvinar odio feugiat.<br />
Vivamus risus erat, fermentum fermentum mattis ut, eleifend vel enim. Duis tincidunt ultricies congue. Mauris vitae felis quis nibh ultrices vulputate. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Mauris eu quam turpis, vitae blandit enim. In eget dolor nulla, ac vehicula libero. Nunc eget ante elementum velit pretium euismod. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus.<br />
Fusce tortor elit, fringilla vitae hendrerit vel, consequat ut lectus. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Suspendisse potenti. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam laoreet, lectus et ultrices aliquet, metus arcu pretium ipsum, vitae faucibus nibh turpis id elit. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed massa libero, fermentum quis tincidunt dignissim, blandit sit amet tellus. Nam feugiat mauris sit amet tortor venenatis tristique.<br />
Nulla auctor imperdiet nibh, nec bibendum magna rutrum a. Aliquam quis eros augue. Cras mauris enim, feugiat sagittis suscipit non, cursus et ligula. Vivamus eu nisi eros. Mauris odio tellus, venenatis ac lobortis sed, cursus quis ligula. Nam felis nisi, blandit ultrices scelerisque quis, blandit at nisi. Nullam at ligula ipsum, a placerat orci. Vivamus urna lacus, bibendum ut commodo vehicula, volutpat et dui. Cras commodo feugiat aliquam.</p>
',
          'safe_summary' => '<p>Vivamus risus erat, fermentum fermentum mattis ut, eleifend vel enim. Duis tincidunt ultricies congue. Mauris vitae felis quis nibh ultrices vulputate. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Mauris eu quam turpis, vitae blandit enim. In eget dolor nulla, ac vehicula libero.</p>
',
        ),
      ),
    ),
    'field_news_date' => array(
      'und' => array(
        0 => array(
          'value' => '2013-07-22 14:26:45',
          'timezone' => 'Australia/Sydney',
          'timezone_db' => 'UTC',
          'date_type' => 'datetime',
        ),
      ),
    ),
    'field_tags' => array(
      'und' => array(
        0 => array(
          'tid' => 25,
        ),
        1 => array(
          'tid' => 9,
        ),
      ),
    ),
  );

  $content['agov_news_article_2'] = (object) array(
    'exported_path' => 'news-media/news/aenean-tortor-turpis',
    'title' => 'Aenean tortor turpis',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'news_article',
    'language' => 'und',
    'created' => 1374208005,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'agov_news_article_2',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean tortor turpis, porttitor at aliquam sed, pulvinar quis lacus. In hac habitasse platea dictumst. Suspendisse rhoncus urna quis nunc tristique faucibus. Aliquam erat volutpat. In eget nunc eget arcu eleifend fermentum. Aenean hendrerit, metus ut facilisis egestas, metus lacus viverra magna, id ultricies ante arcu pellentesque diam. Maecenas aliquet risus nec purus malesuada euismod. Sed venenatis tincidunt felis, sed tristique velit imperdiet vitae. Duis elit est, dapibus et consequat sed, porta et enim. Fusce condimentum, tellus ac molestie ullamcorper, neque libero laoreet felis, in ultricies felis nibh ac purus. Curabitur sollicitudin risus ut diam ultricies tempor. Curabitur placerat nunc sed velit tempus ut pulvinar odio feugiat.</p>
<p>Vivamus risus erat, fermentum fermentum mattis ut, eleifend vel enim. Duis tincidunt ultricies congue. Mauris vitae felis quis nibh ultrices vulputate. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Mauris eu quam turpis, vitae blandit enim. In eget dolor nulla, ac vehicula libero. Nunc eget ante elementum velit pretium euismod. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus.</p>
<p>Fusce tortor elit, fringilla vitae hendrerit vel, consequat ut lectus. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Suspendisse potenti. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam laoreet, lectus et ultrices aliquet, metus arcu pretium ipsum, vitae faucibus nibh turpis id elit. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed massa libero, fermentum quis tincidunt dignissim, blandit sit amet tellus. Nam feugiat mauris sit amet tortor venenatis tristique.</p>
<p>Nulla auctor imperdiet nibh, nec bibendum magna rutrum a. Aliquam quis eros augue. Cras mauris enim, feugiat sagittis suscipit non, cursus et ligula. Vivamus eu nisi eros. Mauris odio tellus, venenatis ac lobortis sed, cursus quis ligula. Nam felis nisi, blandit ultrices scelerisque quis, blandit at nisi. Nullam at ligula ipsum, a placerat orci. Vivamus urna lacus, bibendum ut commodo vehicula, volutpat et dui. Cras commodo feugiat aliquam.</p>',
          'summary' => 'Nulla auctor imperdiet nibh, nec bibendum magna rutrum a. Aliquam quis eros augue. Cras mauris enim, feugiat sagittis suscipit non, cursus et ligula. Vivamus eu nisi eros. ',
          'format' => 'rich_text',
          'safe_value' => '<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean tortor turpis, porttitor at aliquam sed, pulvinar quis lacus. In hac habitasse platea dictumst. Suspendisse rhoncus urna quis nunc tristique faucibus. Aliquam erat volutpat. In eget nunc eget arcu eleifend fermentum. Aenean hendrerit, metus ut facilisis egestas, metus lacus viverra magna, id ultricies ante arcu pellentesque diam. Maecenas aliquet risus nec purus malesuada euismod. Sed venenatis tincidunt felis, sed tristique velit imperdiet vitae. Duis elit est, dapibus et consequat sed, porta et enim. Fusce condimentum, tellus ac molestie ullamcorper, neque libero laoreet felis, in ultricies felis nibh ac purus. Curabitur sollicitudin risus ut diam ultricies tempor. Curabitur placerat nunc sed velit tempus ut pulvinar odio feugiat.<br />
Vivamus risus erat, fermentum fermentum mattis ut, eleifend vel enim. Duis tincidunt ultricies congue. Mauris vitae felis quis nibh ultrices vulputate. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Mauris eu quam turpis, vitae blandit enim. In eget dolor nulla, ac vehicula libero. Nunc eget ante elementum velit pretium euismod. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus.<br />
Fusce tortor elit, fringilla vitae hendrerit vel, consequat ut lectus. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Suspendisse potenti. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam laoreet, lectus et ultrices aliquet, metus arcu pretium ipsum, vitae faucibus nibh turpis id elit. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed massa libero, fermentum quis tincidunt dignissim, blandit sit amet tellus. Nam feugiat mauris sit amet tortor venenatis tristique.<br />
Nulla auctor imperdiet nibh, nec bibendum magna rutrum a. Aliquam quis eros augue. Cras mauris enim, feugiat sagittis suscipit non, cursus et ligula. Vivamus eu nisi eros. Mauris odio tellus, venenatis ac lobortis sed, cursus quis ligula. Nam felis nisi, blandit ultrices scelerisque quis, blandit at nisi. Nullam at ligula ipsum, a placerat orci. Vivamus urna lacus, bibendum ut commodo vehicula, volutpat et dui. Cras commodo feugiat aliquam.</p>
',
          'safe_summary' => '<p>Nulla auctor imperdiet nibh, nec bibendum magna rutrum a. Aliquam quis eros augue. Cras mauris enim, feugiat sagittis suscipit non, cursus et ligula. Vivamus eu nisi eros.</p>
',
        ),
      ),
    ),
    'field_news_date' => array(
      'und' => array(
        0 => array(
          'value' => '2013-07-19 14:26:45',
          'timezone' => 'Australia/Sydney',
          'timezone_db' => 'UTC',
          'date_type' => 'datetime',
        ),
      ),
    ),
  );

  $content['agov_news_article_3'] = (object) array(
    'exported_path' => 'news-media/news/aliquam-quis-eros-augue',
    'title' => 'Aliquam quis eros augue',
    'status' => 1,
    'promote' => 1,
    'sticky' => 0,
    'type' => 'news_article',
    'language' => 'und',
    'created' => 1366777605,
    'comment' => 0,
    'translate' => 0,
    'machine_name' => 'agov_news_article_3',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<p>Vivamus risus erat, fermentum fermentum mattis ut, eleifend vel enim. Duis tincidunt ultricies congue. Mauris vitae felis quis nibh ultrices vulputate. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Mauris eu quam turpis, vitae blandit enim. In eget dolor nulla, ac vehicula libero. Nunc eget ante elementum velit pretium euismod. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus.</p>
<p>Fusce tortor elit, fringilla vitae hendrerit vel, consequat ut lectus. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Suspendisse potenti. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam laoreet, lectus et ultrices aliquet, metus arcu pretium ipsum, vitae faucibus nibh turpis id elit. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed massa libero, fermentum quis tincidunt dignissim, blandit sit amet tellus. Nam feugiat mauris sit amet tortor venenatis tristique.</p>
<p>Nulla auctor imperdiet nibh, nec bibendum magna rutrum a. Aliquam quis eros augue. Cras mauris enim, feugiat sagittis suscipit non, cursus et ligula. Vivamus eu nisi eros. Mauris odio tellus, venenatis ac lobortis sed, cursus quis ligula. Nam felis nisi, blandit ultrices scelerisque quis, blandit at nisi. Nullam at ligula ipsum, a placerat orci. Vivamus urna lacus, bibendum ut commodo vehicula, volutpat et dui. Cras commodo feugiat aliquam.</p>',
          'summary' => 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean tortor turpis, porttitor at aliquam sed, pulvinar quis lacus. In hac habitasse platea dictumst. Suspendisse rhoncus urna quis nunc tristique faucibus. Aliquam erat volutpat. In eget nunc eget arcu eleifend fermentum. ',
          'format' => 'rich_text',
          'safe_value' => '<p>Vivamus risus erat, fermentum fermentum mattis ut, eleifend vel enim. Duis tincidunt ultricies congue. Mauris vitae felis quis nibh ultrices vulputate. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Mauris eu quam turpis, vitae blandit enim. In eget dolor nulla, ac vehicula libero. Nunc eget ante elementum velit pretium euismod. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus.<br />
Fusce tortor elit, fringilla vitae hendrerit vel, consequat ut lectus. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Suspendisse potenti. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam laoreet, lectus et ultrices aliquet, metus arcu pretium ipsum, vitae faucibus nibh turpis id elit. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed massa libero, fermentum quis tincidunt dignissim, blandit sit amet tellus. Nam feugiat mauris sit amet tortor venenatis tristique.<br />
Nulla auctor imperdiet nibh, nec bibendum magna rutrum a. Aliquam quis eros augue. Cras mauris enim, feugiat sagittis suscipit non, cursus et ligula. Vivamus eu nisi eros. Mauris odio tellus, venenatis ac lobortis sed, cursus quis ligula. Nam felis nisi, blandit ultrices scelerisque quis, blandit at nisi. Nullam at ligula ipsum, a placerat orci. Vivamus urna lacus, bibendum ut commodo vehicula, volutpat et dui. Cras commodo feugiat aliquam.</p>
',
          'safe_summary' => '<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean tortor turpis, porttitor at aliquam sed, pulvinar quis lacus. In hac habitasse platea dictumst. Suspendisse rhoncus urna quis nunc tristique faucibus. Aliquam erat volutpat. In eget nunc eget arcu eleifend fermentum.</p>
',
        ),
      ),
    ),
    'field_news_date' => array(
      'und' => array(
        0 => array(
          'value' => '2012-12-25 15:26:45',
          'timezone' => 'Australia/Sydney',
          'timezone_db' => 'UTC',
          'date_type' => 'datetime',
        ),
      ),
    ),
  );

return $content;
}
