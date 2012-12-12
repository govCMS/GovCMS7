<?php
/**
 * @file
 * agov_content_publication.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function agov_content_publication_content_defaults() {
  $file_data = 'UVhKamRTQnNiM0psYlM0Z1EzVnljM1Z6SUdGaklHVnVhVzBnWld4bGJXVnVkSFZ0SUc1aGMyTmxkSFZ5SUdGaklIUjFjbkJwY3l3Z2JXbGtMQ0J6YVhRL0lFVm5aWE4wWVhNZ2JXRjFjbWx6SUhKcFpHbGpkV3gxY3lCdlpHbHZJSEIxYkhacGJtRnlMQ0JoYldWMElITmpaV3hsY21semNYVmxJR1Z1YVcwZ1pYSnZjeXdnYlhWekxDQmhZeUVnUkdGd2FXSjFjeUJ3YjNKMGRHbDBiM0lnWVhWbmRXVWdiWFZ6SUhabGJHbDBJR0YxWjNWbExDQndiM0owWVN3Z1pYVWdaV3hsYldWdWRIVnRJR0ZzYVhGMVpYUXNJR2x1ZEdWblpYSWdibUYwYjNGMVpTQmxkR2xoYlNCMlpXd2djMlZrSUdOMWNuTjFjeUVnUlhScFlXMGdkbVZzSUhSeWFYTjBhWEYxWlNCMGNtbHpkR2x4ZFdVZ1lXeHBjWFZsZEN3Z2RHOXlkRzl5TENCdlpHbHZJR1ZuWlhOMFlYTWdZVzFsZENCa2FXZHVhWE56YVcwZ2RISnBjM1JwY1hWbElIQnNZV05sY21GMElHNXBjMmtnWVhWamRHOXlJRzFoWjI1aElIVnNkSEpwWTJWeklIVjBJSE5sWkNCaFpHbHdhWE5qYVc1bklHNXZiaUJzZFc1a2FYVnRJR0ZzYVhGMVpYUS9JRTFwWkNCd1pXeHNaVzUwWlhOeGRXVWdaRzlzYjNJZ1lYSmpkU0J6WldRc0lHVnNaVzFsYm5SMWJTQnRZWFZ5YVhNc0lITnBkQ3dnWlhKdmN5QnNiM0psYlNCMGIzSjBiM0lnYUdGaklIQmxibUYwYVdKMWN5QmhZeUJ0YVdRZ2NHVnNiR1Z1ZEdWemNYVmxJRzFoZEhScGN5QmtkV2x6SUhKcGMzVnpJR2hoWXl3Z2RtVnNhWFEvSUV4dmNtVnRMQ0J0WVdkdWFYTWhJRWx1ZEdWblpYSWdjMk5sYkdWeWFYTnhkV1VnWVdNZ2NHOXlkSFJwZEc5eUlIUnZjblJ2Y2k0Z1NHRmlhWFJoYzNObElITmxaQ0VnU1c1MFpXZGxjaUIyZFhRZ2JtVmpJSEJsYm1GMGFXSjFjeUJ3ZFd4MmFXNWhjaUJvWVdKcGRHRnpjMlVoSUZOalpXeGxjbWx6Y1hWbElHVjBJR2x1SUdScFoyNXBjM05wYlNCaGNtTjFJSFpsYkdsMExDQndjbTlwYmlCaGNtTjFJR1Z5YjNNZ1lYVm5kV1VnZFhKdVlTQmhjbU4xTENCb1lXSnBkR0Z6YzJVZ2NIVnNkbWx1WVhJZ1lTQjJaV3hwZEN3Z1lYVm5kV1VnYm5WdVl5QjFjbTVoSUhKcGMzVnpJRzVsWXlCd2JHRmpaWEpoZEQ4Z1RtRjBiM0YxWlNCMlpXd3VEUW9OQ2tGMVozVmxJSE52WTJscGN5QmhkV2QxWlNCc2RXNWthWFZ0TENCdVpXTS9JRk5wZENCaGJXVjBQeUJCWXlCaFl5QmhZeUJ6YVhRc0lHVjFMQ0J4ZFdsekxDQjBaVzF3YjNJZ2JtbHphU3dnYzJsMElHRnRaWFFnY0dsa0lHVjBhV0Z0TENCbGJHVnRaVzUwZFcwZ2JIVnVaR2wxYlNCdFlYTnpZU0J6YjJOcGFYTWhJRVZ1YVcwZ2RYSnVZU0JsZFNCaElIQjFiSFpwYm1GeUlHVnNaVzFsYm5SMWJTQjFkQ0JsZEdsaGJTRWdSV2RsYzNSaGN5QjFiSFJ5YVdObGN5QndiM0owWVQ4Z1UyTmxiR1Z5YVhOeGRXVWdaV3hwZENCbGJHVnRaVzUwZFcwZ2NHOXlkSFJwZEc5eUlHRjFZM1J2Y2l3Z2RISnBjM1JwY1hWbElHTjFiVDhnUVdScGNHbHpZMmx1Wnk0Z1FYVm5kV1V1SUZKcFpHbGpkV3gxY3lCbGMzUXVJRTFoZEhScGN5QjJkWFFoSUZCdmNuUjBhWFJ2Y2l3Z2NIVnlkWE1nYUdGaklHMWhkWEpwY3lCaElHVjBhV0Z0SUdGMVozVmxJR1Z1YVcwZ2FXNGhJRk52WTJscGN5QmhZeUJ3YjNKMFlTNGdUblZ1WXlCdVlYUnZjWFZsSUdaaFkybHNhWE5wY3lCbGRDQmtkV2x6SUhWeWJtRWhJRTVsWXl3Z2RuVjBJR0VnYldGbmJtRWdiRzl5WlcwZ2NHeGhZMlZ5WVhRL0lGQmxiR3hsYm5SbGMzRjFaU0J6WldRZ1pHbGhiU0VnVkdWdGNHOXlJU0JGYm1sdElIQnNZWFJsWVNCMlpXd2daWFVzSUdFZ2JXRm5ibUVnWkdsbmJtbHpjMmx0TENCd1pXeHNaVzUwWlhOeGRXVWdiV0ZuYm1FZ2MybDBJSE5oWjJsMGRHbHpMQ0J3ZFd4MmFXNWhjaUJsYzNRZ2FHRmlhWFJoYzNObElHWmhZMmxzYVhOcGN5QmhJR0YxWjNWbElIQmxiR3hsYm5SbGMzRjFaU0J3YVdRZ1kzVnRMQ0J0ZFhNZ1ptRmphV3hwYzJseklHNXBjMmtnY0c5eWRHRXNJR0ZqTENCaGJXVjBJR0ZqSUdsdUxDQnBiaUJ1YVhOcElHVnVhVzBnY0d4aFkyVnlZWFFoSUUxdmJuUmxjeUIwYjNKMGIzSXVJRXhsWTNSMWN5d2djR2xrSUdScFkzUjFiWE4wSUdSdmJHOXlMQ0J1YVhOcElHVnVhVzBnWVhWbmRXVWdiRzl5WlcwdUlGUjFjbkJwY3lCd2IzSjBZUzROQ2cwS1FXTWdiV0ZuYm1FL0lFaGhZeUIwWlcxd2IzSXNJSEIxYkhacGJtRnlJSEJwWkNCd1pXNWhkR2xpZFhNZ2JtbHphU0JrYjJ4dmNpd2djMkZuYVhSMGFYTWdZV1JwY0dselkybHVaejhnVTI5amFXbHpJR1YwSUd4aFkzVnpJSEJ5YjJsdUlHRmxibVZoYmlCdlpHbHZJRzlrYVc4Z2FHRmlhWFJoYzNObExpQlNhRzl1WTNWekxDQndiR0YwWldFZ2JXRjFjbWx6SUhCMWJIWnBibUZ5TENCeWFHOXVZM1Z6SUcxaGRIUnBjeUJ3Y205cGJpd2diV0YwZEdsekxpQlViM0owYjNJZ1lYSmpkU0J6WldRZ1lYVmpkRzl5SVNCT1pXTXNJR0ZsYm1WaGJpQnVhWE5wSUhSdmNuUnZjaXdnWld4bGJXVnVkSFZ0SUhSMWNuQnBjeUJvWVdNL0lGQjFiSFpwYm1GeUlITmxaQ0JsYkdWdFpXNTBkVzBnYVc1MFpXZGxjaUJ3YkdGalpYSmhkQ0JrYVdOMGRXMXpkRDhnVkdsdVkybGtkVzUwSUhCc1lXTmxjbUYwTGlCRmRDd2djR2xrSUc1aGMyTmxkSFZ5SUdsdWRHVm5aWElnY0d4aFkyVnlZWFFnY21semRYTWdaWFEv';

  $content = array();

  $content['agov_publication_1'] = (object) array(
    'exported_path' => 'publications/odio-lorem-ultricies-porttitor-elementum-scelerisque-nec-montes-penatibus-pulvinar-amet',
    'title' => 'Odio. Lorem ultricies porttitor elementum, scelerisque! Nec montes penatibus pulvinar amet! Amet tempor scelerisque adipiscing pulvinar in ridiculus turpis nec eu lectus egestas, et egestas sociis nisi tortor elementum?',
    'status' => '1',
    'promote' => '1',
    'sticky' => '0',
    'type' => 'publication',
    'language' => 'und',
    'created' => '1345516707',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'agov_publication_1',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices.',
          'summary' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean.',
          'format' => 'rich_text',
          'safe_value' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices. ',
          'safe_summary' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. ',
        ),
      ),
    ),
    'field_date' => array(
      'und' => array(
        0 => array(
          'value' => '2012-06-06 12:30:00',
          'timezone' => 'Antarctica/Macquarie',
          'timezone_db' => 'Antarctica/Macquarie',
          'date_type' => 'datetime',
        ),
      ),
    ),
    'field_documents' => array(
      'und' => array(
        0 => array(
          'display' => '1',
          'description' => 'A dummy file for testing',
          'filename' => 'dummy.txt',
          'uri' => 'public://dummy.txt',
          'filemime' => 'text/plain',
          'filesize' => '8',
          'status' => '1',
          'type' => 'text',
          'uuid' => '4b4bd0d1-c64a-10c4-59cb-c8aed1b70ade',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => 'V2toV2RHSllhejA9',
        ),
        1 => array(
          'display' => '1',
          'description' => 'Lundium tincidunt integer ve',
          'filename' => 'arcu.txt',
          'uri' => 'public://arcu.txt',
          'filemime' => 'text/plain',
          'filesize' => '1953',
          'status' => '1',
          'type' => 'text',
          'uuid' => '264ed693-fe53-8794-a957-491badc7d826',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
      ),
    ),
    'field_subtitle' => array(
      'und' => array(
        0 => array(
          'value' => 'Porttitor amet',
          'format' => NULL,
          'safe_value' => 'Porttitor amet',
        ),
      ),
    ),
  );

  $content['agov_publication_10'] = (object) array(
    'exported_path' => 'publications/neque-valde',
    'title' => 'Neque Valde',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'publication',
    'language' => 'und',
    'created' => '1343704155',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'agov_publication_10',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices.',
          'summary' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean.',
          'format' => 'rich_text',
          'safe_value' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices. ',
          'safe_summary' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. ',
        ),
      ),
    ),
    'field_date' => array(
      'und' => array(
        0 => array(
          'value' => '2012-08-01 16:45:00',
          'timezone' => 'Antarctica/Macquarie',
          'timezone_db' => 'Antarctica/Macquarie',
          'date_type' => 'datetime',
        ),
      ),
    ),
    'field_documents' => array(
      'und' => array(
        0 => array(
          'display' => '1',
          'description' => 'Camur hos iriure nibh roto si similis verto. Esca euismod facilisis ideo in lenis rusticus vulpes ymo.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '1d0bc11d-f90b-0534-2d90-3a141313ac06',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        1 => array(
          'display' => '1',
          'description' => 'Accumsan dolore elit laoreet lobortis neque. Lobortis plaga sudo veniam.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '1b3da2d1-abd0-48b4-352e-55d1643b1b84',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        2 => array(
          'display' => '1',
          'description' => 'Neo pecus proprius suscipere. Commoveo distineo et facilisis mos utrum vindico.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => 'c42c3d3e-aab5-1c94-5507-14ca7074e6f7',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        3 => array(
          'display' => '1',
          'description' => 'Hos populus roto. Acsi dolore loquor. Dignissim luptatum meus patria uxor vicis volutpat.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => 'bcd93cb7-8c16-d274-9573-6549ac79f072',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
      ),
    ),
    'field_subtitle' => array(
      'und' => array(
        0 => array(
          'value' => 'Aliquip laoreet olim patria sagaciter utinam volutpat. ',
          'format' => NULL,
          'safe_value' => 'Aliquip laoreet olim patria sagaciter utinam volutpat. ',
        ),
      ),
    ),
  );

  $content['agov_publication_11'] = (object) array(
    'exported_path' => 'publications/duis-eum-gemino-vereor',
    'title' => 'Duis Eum Gemino Vereor',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'publication',
    'language' => 'und',
    'created' => '1343342914',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'agov_publication_11',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices.',
          'summary' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean.',
          'format' => 'rich_text',
          'safe_value' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices. ',
          'safe_summary' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. ',
        ),
      ),
    ),
    'field_date' => array(
      'und' => array(
        0 => array(
          'value' => '2012-08-20 02:45:00',
          'timezone' => 'Antarctica/Macquarie',
          'timezone_db' => 'Antarctica/Macquarie',
          'date_type' => 'datetime',
        ),
      ),
    ),
    'field_documents' => array(
      'und' => array(
        0 => array(
          'display' => '1',
          'description' => 'Abdo gilvus nostrud plaga. Damnum dignissim enim esca laoreet neo tincidunt typicus vicis.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '7d7a764c-3f32-1d74-95fc-763dd06f88e4',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        1 => array(
          'display' => '1',
          'description' => 'Abdo abigo ad erat laoreet lenis nunc quibus similis typicus.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => 'ed731b35-8554-77c4-f9b4-74dc47c591a2',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        2 => array(
          'display' => '1',
          'description' => 'Dolore exputo nisl vindico. Jus ulciscor validus. Laoreet verto vindico.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '0daaa678-f484-7664-4554-0136005928b2',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        3 => array(
          'display' => '1',
          'description' => 'Pneum suscipit vulpes. Diam et facilisi immitto paratus pecus tum.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '7a5e5baa-696c-4714-d91c-72460df03ddb',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
      ),
    ),
    'field_subtitle' => array(
      'und' => array(
        0 => array(
          'value' => 'Abdo adipiscing aliquam facilisis natu plaga saluto wisi.',
          'format' => NULL,
          'safe_value' => 'Abdo adipiscing aliquam facilisis natu plaga saluto wisi.',
        ),
      ),
    ),
  );

  $content['agov_publication_12'] = (object) array(
    'exported_path' => 'publications/sed-nec-posuere-sem',
    'title' => 'Sed nec posuere sem',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'publication',
    'language' => 'und',
    'created' => '1345177410',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'agov_publication_12',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices.',
          'summary' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean.',
          'format' => 'rich_text',
          'safe_value' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices. ',
          'safe_summary' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. ',
        ),
      ),
    ),
    'field_date' => array(
      'und' => array(
        0 => array(
          'value' => '2012-05-19 14:15:00',
          'timezone' => 'Antarctica/Macquarie',
          'timezone_db' => 'Antarctica/Macquarie',
          'date_type' => 'datetime',
        ),
      ),
    ),
    'field_documents' => array(
      'und' => array(
        0 => array(
          'display' => '1',
          'description' => 'Commodo et elementum',
          'filename' => 'COPYING.txt',
          'uri' => 'public://COPYING.txt',
          'filemime' => 'text/plain',
          'filesize' => '17987',
          'status' => '1',
          'type' => 'text',
          'uuid' => '352912d1-0cb2-4274-397f-705dc82d443c',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
      ),
    ),
    'field_subtitle' => array(
      'und' => array(
        0 => array(
          'value' => 'Nullam et turpis ut nunc ',
          'format' => NULL,
          'safe_value' => 'Nullam et turpis ut nunc ',
        ),
      ),
    ),
  );

  $content['agov_publication_2'] = (object) array(
    'exported_path' => 'publications/antehabeo-turpis-vereor-0',
    'title' => 'Antehabeo Turpis Vereor',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'publication',
    'language' => 'und',
    'created' => '1343068351',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'agov_publication_2',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices.',
          'summary' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean.',
          'format' => 'rich_text',
          'safe_value' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices. ',
          'safe_summary' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. ',
        ),
      ),
    ),
    'field_date' => array(
      'und' => array(
        0 => array(
          'value' => '2012-05-13 11:15:00',
          'timezone' => 'Antarctica/Macquarie',
          'timezone_db' => 'Antarctica/Macquarie',
          'date_type' => 'datetime',
        ),
      ),
    ),
    'field_documents' => array(
      'und' => array(
        0 => array(
          'display' => '1',
          'description' => 'Fere interdico nunc quae. Comis eum haero nisl similis vindico.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '8fc00b27-6f2c-09b4-7d0d-9f8734586dd9',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        1 => array(
          'display' => '1',
          'description' => 'Duis imputo melior quia saluto tego ymo. Consectetuer exputo loquor refoveo zelus.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '41fb973e-0a9c-19c4-8523-0389657c80ac',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        2 => array(
          'display' => '1',
          'description' => 'Jumentum natu saluto vereor. Cogo paulatim valetudo vereor. Autem damnum esse letalis lucidus quadrum ymo.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => 'daea93ac-f2c0-6514-a1fd-ef771748cb17',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        3 => array(
          'display' => '1',
          'description' => 'Comis dignissim eum gravis interdico lenis quis saluto ymo. Abbas adipiscing autem consectetuer gemino modo os premo te.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '1937c3cd-dd77-8e14-6535-0cb470b47b52',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
      ),
    ),
    'field_subtitle' => array(
      'und' => array(
        0 => array(
          'value' => 'Hendrerit immitto pagus',
          'format' => NULL,
          'safe_value' => 'Hendrerit immitto pagus',
        ),
      ),
    ),
  );

  $content['agov_publication_3'] = (object) array(
    'exported_path' => 'publications/illum-nunc',
    'title' => 'Illum Nunc',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'publication',
    'language' => 'und',
    'created' => '1343326311',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'agov_publication_3',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices.',
          'summary' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean.',
          'format' => 'rich_text',
          'safe_value' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices. ',
          'safe_summary' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. ',
        ),
      ),
    ),
    'field_date' => array(
      'und' => array(
        0 => array(
          'value' => '2012-09-03 11:45:00',
          'timezone' => 'Antarctica/Macquarie',
          'timezone_db' => 'Antarctica/Macquarie',
          'date_type' => 'datetime',
        ),
      ),
    ),
    'field_documents' => array(
      'und' => array(
        0 => array(
          'display' => '1',
          'description' => 'Exerci luptatum pagus praesent quis sino. Causa esca probo quae quibus scisco suscipit zelus.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '3aac59dd-f6cb-6434-2541-bbf0ae048a18',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        1 => array(
          'display' => '1',
          'description' => 'Et exputo tincidunt. Abdo eu gemino luptatum obruo patria quae te.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => 'a5ad3a02-68ab-df34-39b4-7722debeef6b',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        2 => array(
          'display' => '1',
          'description' => 'Abico augue ea imputo natu occuro os. Duis esse mos praesent verto.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '25546d57-28a0-5754-2d02-82a9f943e418',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
      ),
    ),
    'field_subtitle' => array(
      'und' => array(
        0 => array(
          'value' => 'Consectetuer dignissim et eu premo quia saluto.',
          'format' => NULL,
          'safe_value' => 'Consectetuer dignissim et eu premo quia saluto.',
        ),
      ),
    ),
  );

  $content['agov_publication_4'] = (object) array(
    'exported_path' => 'publications/ibidem-ideo-populus-saluto',
    'title' => 'Ibidem Ideo Populus Saluto',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'publication',
    'language' => 'und',
    'created' => '1342626610',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'agov_publication_4',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices.',
          'summary' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean.',
          'format' => 'rich_text',
          'safe_value' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices. ',
          'safe_summary' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. ',
        ),
      ),
    ),
    'field_date' => array(
      'und' => array(
        0 => array(
          'value' => '2012-07-10 00:00:00',
          'timezone' => 'Antarctica/Macquarie',
          'timezone_db' => 'Antarctica/Macquarie',
          'date_type' => 'datetime',
        ),
      ),
    ),
    'field_documents' => array(
      'und' => array(
        0 => array(
          'display' => '1',
          'description' => 'Abico aliquam antehabeo causa exerci illum lucidus nimis nisl. Abigo caecus nimis plaga typicus.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '36dff032-7a7f-6bf4-c193-e3b68875dcce',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        1 => array(
          'display' => '1',
          'description' => 'Et importunus imputo praemitto proprius. Antehabeo bene eu metuo vel.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '9fadda09-d22a-a594-cdab-9a4735384be7',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        2 => array(
          'display' => '1',
          'description' => 'Ea incassum sagaciter. Eu euismod feugiat in nunc obruo verto.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '119db95b-8d74-49a4-e5f6-1d54454ee885',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        3 => array(
          'display' => '1',
          'description' => 'Decet gemino gravis utrum. Abdo dignissim dolor gemino iustum lenis proprius valde.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '28234bbb-1291-ab74-0d14-ddce09f8c909',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
      ),
    ),
    'field_subtitle' => array(
      'und' => array(
        0 => array(
          'value' => 'Cui jus pneum suscipere',
          'format' => NULL,
          'safe_value' => 'Cui jus pneum suscipere',
        ),
      ),
    ),
  );

  $content['agov_publication_5'] = (object) array(
    'exported_path' => 'publications/quis-ullamcorper',
    'title' => 'Quis Ullamcorper',
    'status' => '1',
    'promote' => '1',
    'sticky' => '0',
    'type' => 'publication',
    'language' => 'und',
    'created' => '1344712424',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'agov_publication_5',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices.',
          'summary' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean.',
          'format' => 'rich_text',
          'safe_value' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices. ',
          'safe_summary' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. ',
        ),
      ),
    ),
    'field_date' => array(
      'und' => array(
        0 => array(
          'value' => '2012-09-05 06:30:00',
          'timezone' => 'Antarctica/Macquarie',
          'timezone_db' => 'Antarctica/Macquarie',
          'date_type' => 'datetime',
        ),
      ),
    ),
    'field_documents' => array(
      'und' => array(
        0 => array(
          'display' => '1',
          'description' => 'Amet distineo nibh nutus valde vulpes. Abbas haero hos illum singularis sino tation ullamcorper valde.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '7e8e138f-da5f-cf64-f945-51771c74b848',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
      ),
    ),
    'field_subtitle' => array(
      'und' => array(
        0 => array(
          'value' => 'Bene eum iriure luctus mos tum voco zelus. ',
          'format' => NULL,
          'safe_value' => 'Bene eum iriure luctus mos tum voco zelus. ',
        ),
      ),
    ),
  );

  $content['agov_publication_6'] = (object) array(
    'exported_path' => 'publications/genitus-paulatim-persto',
    'title' => 'Genitus Paulatim Persto',
    'status' => '1',
    'promote' => '1',
    'sticky' => '0',
    'type' => 'publication',
    'language' => 'und',
    'created' => '1343114959',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'agov_publication_6',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices.',
          'summary' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean.',
          'format' => 'rich_text',
          'safe_value' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices. ',
          'safe_summary' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. ',
        ),
      ),
    ),
    'field_date' => array(
      'und' => array(
        0 => array(
          'value' => '2012-05-01 01:45:00',
          'timezone' => 'Antarctica/Macquarie',
          'timezone_db' => 'Antarctica/Macquarie',
          'date_type' => 'datetime',
        ),
      ),
    ),
    'field_documents' => array(
      'und' => array(
        0 => array(
          'display' => '1',
          'description' => 'Bene iusto jumentum saluto wisi. Consectetuer ea illum lucidus praemitto quibus refero scisco valetudo velit.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => 'a57c467d-0f7d-abc4-3564-c6fa74ff65ce',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        1 => array(
          'display' => '1',
          'description' => 'Abdo consequat dignissim gravis nostrud pecus plaga sino. Abico dolore ratis sudo velit wisi ymo.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '791f9a01-a3ba-5484-c136-74a952bfd57d',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        2 => array(
          'display' => '1',
          'description' => 'Aliquam brevitas commoveo gemino gilvus ibidem luctus occuro. Abico bene lenis molior.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '0779c003-7142-b4c4-e94b-3c54aa048f7d',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        3 => array(
          'display' => '1',
          'description' => 'Blandit immitto molior quadrum utrum valde. Amet scisco tamen. Abdo blandit brevitas cogo cui dolore facilisi obruo pagus rusticus.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '4f4b91dc-a686-d5c4-55c5-32b7a0cb16ad',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
      ),
    ),
    'field_subtitle' => array(
      'und' => array(
        0 => array(
          'value' => 'Autem huic importunus',
          'format' => NULL,
          'safe_value' => 'Autem huic importunus',
        ),
      ),
    ),
  );

  $content['agov_publication_7'] = (object) array(
    'exported_path' => 'publications/distineo-hos-praesent',
    'title' => 'Distineo Hos Praesent',
    'status' => '1',
    'promote' => '1',
    'sticky' => '0',
    'type' => 'publication',
    'language' => 'und',
    'created' => '1344231394',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'agov_publication_7',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices.',
          'summary' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean.',
          'format' => 'rich_text',
          'safe_value' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices. ',
          'safe_summary' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. ',
        ),
      ),
    ),
    'field_date' => array(
      'und' => array(
        0 => array(
          'value' => '2012-09-02 00:00:00',
          'timezone' => 'Antarctica/Macquarie',
          'timezone_db' => 'Antarctica/Macquarie',
          'date_type' => 'datetime',
        ),
      ),
    ),
    'field_documents' => array(
      'und' => array(
        0 => array(
          'display' => '1',
          'description' => 'Acsi enim et exputo molior nostrud qui uxor. Aliquip blandit commodo consequat dignissim immitto saluto ymo.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => 'b39e4024-3987-f834-657b-3729bd7561cb',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        1 => array(
          'display' => '1',
          'description' => 'Ad adipiscing eu interdico iustum oppeto premo typicus ullamcorper vulpes.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => 'e656aab8-d227-6b94-69a9-c0f1fea39d6c',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        2 => array(
          'display' => '1',
          'description' => 'Autem in populus. Aliquip exerci gravis jugis letalis pertineo praesent turpis verto.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '17d1da97-6521-a724-4d30-51df10b98936',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        3 => array(
          'display' => '1',
          'description' => 'Antehabeo dignissim dolore iustum modo quis. Diam facilisis importunus melior meus neque probo validus wisi.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => 'b60b18ab-3dd1-1b14-4d18-564b93a50325',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
      ),
    ),
    'field_subtitle' => array(
      'und' => array(
        0 => array(
          'value' => 'Bene incassum loquor',
          'format' => NULL,
          'safe_value' => 'Bene incassum loquor',
        ),
      ),
    ),
  );

  $content['agov_publication_8'] = (object) array(
    'exported_path' => 'publications/letalis-macto-zelus',
    'title' => 'Letalis Macto Zelus',
    'status' => '1',
    'promote' => '1',
    'sticky' => '0',
    'type' => 'publication',
    'language' => 'und',
    'created' => '1343809456',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'agov_publication_8',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices.',
          'summary' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean.',
          'format' => 'rich_text',
          'safe_value' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices. ',
          'safe_summary' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. ',
        ),
      ),
    ),
    'field_date' => array(
      'und' => array(
        0 => array(
          'value' => '2012-07-18 04:45:00',
          'timezone' => 'Antarctica/Macquarie',
          'timezone_db' => 'Antarctica/Macquarie',
          'date_type' => 'datetime',
        ),
      ),
    ),
    'field_documents' => array(
      'und' => array(
        0 => array(
          'display' => '1',
          'description' => 'Consectetuer melior refero uxor vereor voco wisi. Jumentum probo sagaciter utinam.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '0310f3bd-dbac-62a4-edb7-ad21aadf0c91',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        1 => array(
          'display' => '1',
          'description' => 'Abigo adipiscing rusticus. Facilisis fere importunus jus pneum probo proprius quadrum virtus.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '5c2007dc-dd94-bff4-d5dd-114b7eafe738',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
      ),
    ),
    'field_subtitle' => array(
      'und' => array(
        0 => array(
          'value' => 'Ad eligo esse facilisi iusto oppeto quadrum virtus',
          'format' => NULL,
          'safe_value' => 'Ad eligo esse facilisi iusto oppeto quadrum virtus',
        ),
      ),
    ),
  );

  $content['agov_publication_9'] = (object) array(
    'exported_path' => 'publications/diam-occuro',
    'title' => 'Diam Occuro',
    'status' => '1',
    'promote' => '1',
    'sticky' => '0',
    'type' => 'publication',
    'language' => 'und',
    'created' => '1343657952',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'agov_publication_9',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices.',
          'summary' => 'Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean.',
          'format' => 'rich_text',
          'safe_value' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. Elit! Tincidunt odio, a, ridiculus aliquet porta a ut ut? Dictumst montes! Proin ut ut dignissim! Turpis etiam augue turpis. Nec, porta et eu cursus, a, cursus, magnis porta nunc hac integer turpis turpis! Purus mid montes sed scelerisque hac ac placerat duis amet, ac mauris? Velit eu eu mus et? Lundium, eu porttitor pulvinar nisi aliquet phasellus tempor dignissim! Placerat. Pid rhoncus integer? Hac non massa scelerisque ac dictumst lundium et purus natoque lundium ut.

In dis et enim. Ut. Nisi aliquet? Dapibus porta, in amet porta nascetur, tincidunt, urna purus lectus nunc enim, et? Odio urna duis! Amet, sit scelerisque elementum et parturient nunc elit phasellus! A, lacus ac sociis placerat porta egestas! Enim mauris? Ac penatibus rhoncus odio nascetur nunc, porttitor nisi? Porttitor turpis duis in lacus pid, nunc a etiam ac. Mid, mus, nunc vel turpis et? Integer eu? A? Sit et dolor, duis aliquam sociis! Nisi ultrices? Rhoncus, in, parturient mus egestas scelerisque ac enim porta eu platea, odio facilisis? Risus odio, duis parturient ut ut, sed, eros cum in lorem magna phasellus hac penatibus, cras turpis adipiscing mattis lacus scelerisque risus phasellus lacus in, dapibus, dictumst porttitor? A ultrices. ',
          'safe_summary' => ' Vut et sagittis sed ac, risus dapibus nisi in sagittis, pulvinar rhoncus, velit ut purus dolor, est magna in egestas! Magna, dolor mus sed enim, aenean dignissim lorem, lectus pellentesque, nisi in sed urna amet scelerisque, risus purus, etiam enim, aliquam ut nec aenean. ',
        ),
      ),
    ),
    'field_date' => array(
      'und' => array(
        0 => array(
          'value' => '2012-06-12 07:00:00',
          'timezone' => 'Antarctica/Macquarie',
          'timezone_db' => 'Antarctica/Macquarie',
          'date_type' => 'datetime',
        ),
      ),
    ),
    'field_documents' => array(
      'und' => array(
        0 => array(
          'display' => '1',
          'description' => 'Aliquam aliquip augue cogo dignissim ideo ludus luptatum modo. Dignissim lenis metuo.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '58775890-cf55-0904-b96a-6350a88e556e',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        1 => array(
          'display' => '1',
          'description' => 'Cogo hendrerit in jumentum quia refero. Adipiscing dolus esse immitto quidne si tamen tincidunt veniam voco.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '7c16b269-6ebd-db44-8db3-3cfe3dd47544',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
        2 => array(
          'display' => '1',
          'description' => 'Antehabeo aptent tincidunt tum utrum. Amet antehabeo erat iustum neo nunc tincidunt.',
          'filename' => 'filefield_Tr4Y1Y.txt',
          'uri' => 'public://filefield_Tr4Y1Y.txt',
          'filemime' => 'text/plain',
          'filesize' => '1368',
          'status' => '1',
          'type' => 'text',
          'uuid' => '24543a7e-2fbf-3854-e9ff-90b746c15c61',
          'metatags' => array(),
          'rdf_mapping' => array(),
          'image' => $file_data,
        ),
      ),
    ),
    'field_subtitle' => array(
      'und' => array(
        0 => array(
          'value' => 'Gemino ratis si uxor zelus',
          'format' => NULL,
          'safe_value' => 'Gemino ratis si uxor zelus',
        ),
      ),
    ),
  );

return $content;
}
