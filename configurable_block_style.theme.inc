<?php

function template_preprocess_block_configurable(&$variables) {
  // Re-use all the preprocessing provided by the default block template.
  template_preprocess_block($variables);

  $block = $variables['block'];
  $style = $block->style;

  if ($style->settings['color_type'] === 'custom') {
    $variables['attributes']['style'] .= 'background-color:' . $style->settings['background_color'] . ';';
    $variables['attributes']['style'] .= 'color:' . $style->settings['text_color'] . ';';
  }

  if ($style->settings['height_type'] === 'fixed') {
    $variables['attributes']['style'] .= 'height:' . $style->settings['height_amount'] . $style->settings['height_unit'] . ';';
  }
  if ($style->settings['height_type'] === 'background' && $block->plugin === 'layout:hero') {
    if (!empty($block->settings['image_path'])) {
      $variables['attributes']['style'] .= 'background-size:contain;background-repeat:no-repeat;width:100%;min-height:initial;';
      list($width, $height) = getimagesize(BACKDROP_ROOT . $block->settings['image_path']);
      $variables['attributes']['style'] .= 'height:calc(100vw * ' . $height . ' / ' . $width . ');';
    }
  }
  if ($style->settings['content_container']) {
    $variables['content_container'] = TRUE;
  }
}
