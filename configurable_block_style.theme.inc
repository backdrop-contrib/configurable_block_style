<?php

function template_preprocess_block_configurable(&$variables) {
  // Re-use all the preprocessing provided by the default block template.
  include_once BACKDROP_ROOT . '/core/modules/layout/layout.theme.inc';
  template_preprocess_block($variables);

  $block = $variables['block'];
  $style = $block->style;
  if (empty($variables['attributes']['style'])) {
    $variables['attributes']['style'] = '';
  }

  if ($style->settings['color_type'] === 'custom') {
    // converting to rgba value for purpose of potentially displaying tint
    $rgbabackground = image_hex2rgba($style->settings['background_color']);
    $rgbatext = image_hex2rgba($style->settings['text_color']);

    $variables['attributes']['style'] .= 'background-color: rgb(' . $rgbabackground['red'] . ',' . $rgbabackground['green'] . ',' . $rgbabackground['blue']; 
    if ($style->settings['tint'] == TRUE) {
      $variables['attributes']['style'] .= ',' . $style->settings['tint_value'];
    } 
    $variables['attributes']['style'] .= '); color: rgb(' . $rgbatext['red'] . ',' . $rgbatext['green'] . ',' . $rgbatext['blue'] . ');';
    if ($style->settings['tint'] == TRUE) {
      $variables['attributes']['style'] .= ";" . 'background-blend-mode: multiply;';
    } 
  }

  if ($style->settings['height_type'] === 'fixed') {
    $variables['attributes']['style'] .= 'height:' . $style->settings['height_amount'] . $style->settings['height_unit'] . ';';
  }
  if ($style->settings['height_type'] === 'responsive') {
    $variables['attributes']['style'] .= 'min-height:' . $style->settings['mn_height_amount'] . 'px;' .
      ' height:' . $style->settings['rel_height_amount'] . 'vw;' .
      ' max-height:' . $style->settings['mx_height_amount'] . 'px;';
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
  if ($style->settings['content_padding'] == TRUE) {
    $variables['attributes']['style'] .= 'padding:' .
      $style->settings['padding_top'] . 'px ' .
      $style->settings['padding_right'] . 'px ' .
      $style->settings['padding_bottom'] . 'px ' .
      $style->settings['padding_left'] . 'px;';
  }
}
