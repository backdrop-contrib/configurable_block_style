<?php

function template_preprocess_block_configurable(&$variables) {
  // Re-use all the preprocessing provided by the default block template.
  include_once BACKDROP_ROOT . '/core/modules/layout/layout.theme.inc';
  template_preprocess_block($variables);

  $variables['classes'][] = 'configurable-block-style';

  // Add context classes for admin and dashboard pages.
  if (function_exists('path_is_admin') && path_is_admin(current_path())) {
    $variables['classes'][] = 'admin-panel';
  }
  if (function_exists('current_path') && current_path() === 'admin/dashboard') {
    $variables['classes'][] = 'block-dashboard';
  }

  $block = $variables['block'];
  $style = $block->style;
  if (empty($variables['attributes']['style'])) {
    $variables['attributes']['style'] = '';
  }

  // Color.
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

  // Height.
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

  // Border.
  if ($style->settings['border_type'] === 'custom') {
    $variables['attributes']['style'] .= 'border:' . $style->settings['border_size'] . 'px ' . $style->settings['border_style'] . ' ' . $style->settings['border_color'] . ';';
  }

  // Corners.
  if ($style->settings['corner_type'] === 'round') {
    $variables['attributes']['style'] .= 'border-radius:' . $style->settings['corner_size'] . 'px;';
  }
  if ($style->settings['corner_type'] === 'square') {
    $variables['attributes']['style'] .= 'border-radius:0px;';
  }

  // Shadow.
  if ($style->settings['shadow_type'] === 'custom') {
    $sizes = array();
    $sizes[] = $style->settings['shadow_size'] . 'px' ;
    $sizes[] = $style->settings['shadow_size'] . 'px' ;
    $sizes[] = $style->settings['shadow_size'] * 2 . 'px' ;
    $variables['attributes']['style'] .= 'box-shadow: ' . implode(' ', $sizes) . ' ' . $style->settings['shadow_color'] . ';';
  }

  // Container wrapper.
  if ($style->settings['content_container']) {
    $variables['content_container'] = TRUE;
  }

  // HTML markup settings.
  $variables['wrapper_tag'] = $style->settings['wrapper_tag'];
  $variables['title_tag'] = $style->settings['title_tag'];

  $title_classes = explode(' ', $style->settings['title_classes']);
  foreach ($title_classes as $n => $class) {
    $title_classes[$n] = backdrop_clean_css_identifier($class, array());
  }
  $variables['title_attributes'] = array();
  if (!empty(array_filter($title_classes))) {
    $variables['title_attributes']['class'] = array_filter($title_classes);
  }

  $variables['content_tag'] = $style->settings['content_tag'];
  $content_classes = explode(' ', $style->settings['content_classes']);
  foreach ($content_classes as $n => $class) {
    $content_classes[$n] = backdrop_clean_css_identifier($class, array());
  }
  $variables['content_attributes'] = array();
  if (!empty(array_filter($content_classes))) {
    $variables['content_attributes']['class'] = array_filter($content_classes);
  }

  // Padding.
  if ($style->settings['content_padding'] == TRUE) {
    $variables['attributes']['style'] .= 'padding:' .
      $style->settings['padding_top'] . 'px ' .
      $style->settings['padding_right'] . 'px ' .
      $style->settings['padding_bottom'] . 'px ' .
      $style->settings['padding_left'] . 'px;';
  }

  // Behavior settings: title link, collapsible, block ID.
  $variables['make_title_link'] = !empty($style->settings['make_title_link']);
  $variables['block_title_link'] = !empty($style->settings['block_title_link']) ? $style->settings['block_title_link'] : '';
  $variables['collapsible'] = !empty($style->settings['collapsible']);
  $variables['block_id'] = $block->uuid;

  if ($variables['collapsible']) {
    $variables['classes'][] = 'is-collapsible';
  }
}
