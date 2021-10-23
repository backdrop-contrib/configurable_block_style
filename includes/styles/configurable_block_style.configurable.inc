<?php
/**
 * @file
 * Class providing forms and settings for the default Layout block style.
 */
class ConfigurableBlockStyle extends LayoutHandler {
  /**
   * Indicator as to whether this is a style on the region or on a block.
   *
   * @var boolean
   */
  var $is_region = FALSE;

  /**
   * Constructor for a Layout style class.
   *
   * @param array $plugin_name
   *   The name of the plugin actually being used, which may be pointing at
   *   a parent class of this one.
   * @param array $data
   *   An array of configuration data.
   */
  public function __construct($plugin_name, array $data = array(), $is_region = FALSE) {
    parent::__construct($plugin_name, $data);
    $this->settings += array(
      'classes' => '',
      'content_container' => FALSE,
      'content_padding' => FALSE,
      'color_type' => 'default',
      'background_color' => '#ffffff',
      'text_color' => '#000000',
      'padding_top' => '40',
      'padding_right' => '30',
      'padding_bottom' => '30',
      'padding_left' => '30',
      'height_type' => 'default',
      'height_amount' => '500',
      'mn_height_amount' => '250',
      'rel_height_amount' => '40',
      'mx_height_amount' => '500',
      'tint' => FALSE,
      'tint_value' => '0',
      'height_unit' => 'px',
      'border_type' => 'default',
      'border_size' => '2',
      'border_style' => 'solid',
      'border_color' => '#000000',
      'corner_type' => 'default',
      'corner_size' => '8',
      'shadow_type' => 'default',
      'shadow_size' => '4',
      'shadow_color' => '#000000',
    );
    $this->is_region = $is_region;
  }

  /**
   * Specifies the settings form for configuring the style.
   */
  public function form(&$form, &$form_state) {
    if (!$this->is_region) {

      $form['classes'] = array(
        '#title' => t('Additional CSS classes'),
        '#type' => 'textfield',
        '#default_value' => $this->settings['classes'],
        '#description' => t('Separate multiple classes with spaces.'),
      );

      // Content Container settings.
      $form['content_container'] = array(
        '#title' => t('Content container'),
        '#type' => 'checkbox',
        '#default_value' => $this->settings['content_container'],
        '#description' => t('Add div with container class to align text with other regions.'),
      );

      // Color settings.
      $form['colors'] = array(
        '#title' => t('Colors'),
        '#type' => 'fieldset',
      );
      $form['colors']['color_type'] = array(
        '#type' => 'select',
        '#default_value' => $this->settings['color_type'],
        '#options' => array(
          'default' => 'Use theme colors',
          'custom' => 'Custom colors',
        ),
        '#default_value' => $this->settings['color_type'],
      );
      $form['colors']['background_color'] = array(
        '#title' => t('Background Color'),
        '#type' => 'color',
        '#default_value' => $this->settings['background_color'],
        '#states' => array(
          'invisible' => array(
            ':input[name="style_settings[colors][color_type]"]' => array('value' => 'default'),
          ),
        ),
      );

      $form['colors']['tint'] = array(
        '#title' => t('Tint on background color (or tint over background image).'),
        '#type' => 'checkbox',
        '#default_value' => $this->settings['tint'],
        '#states' => array(
          'invisible' => array(
            ':input[name="style_settings[colors][color_type]"]' => array('value' => 'default'),
          ),
        ),
      );

      $form['colors']['tint_value'] = array(
        '#title' => t('Tint value'),
        '#description' => t('Enter value 0-1 (to represent tint percentage - Example: .45).'),
        '#type' => 'number',
        '#default_value' => $this->settings['tint_value'],
        '#step' => '.01',
        '#attributes' => array(
          'type' => 'number',
          'min' => '0',
          'max' => '1',
        ),
        '#states' => array(
          'visible' => array(
            ':input[name="style_settings[colors][tint]"]' => array('checked' => TRUE),
          ),
        ),
      );

      $form['colors']['text_color'] = array(
        '#title' => t('Text Color'),
        '#type' => 'color',
        '#default_value' => $this->settings['text_color'],
        '#states' => array(
          'invisible' => array(
            ':input[name="style_settings[colors][color_type]"]' => array('value' => 'default'),
          ),
        ),
      );

      // Height settings.
      $form['height'] = array(
        '#title' => t('Height'),
        '#type' => 'fieldset',
      );
      $form['height']['height_type'] = array(
        '#type' => 'select',
        '#options' => array(
          'default' => 'Default',
          'fixed' => 'Fixed height',
          'responsive' => 'Responsive height',
          'background' => 'Fit background image (Hero Blocks)',
        ),
        '#default_value' => $this->settings['height_type'],
      );

      $form['height']['height_amount'] = array(
        '#title' => t('Height'),
        '#type' => 'number',
        '#default_value' => $this->settings['height_amount'],
        '#attributes' => array(
          'type' => 'number',
          'step' => '1',
        ),
        '#states' => array(
          'visible' => array(
            ':input[name="style_settings[height][height_type]"]' => array('value' => 'fixed'),
          ),
        ),
      );
      $form['height']['mn_height_amount'] = array(
        '#title' => t('Minimum height (px)'),
        '#type' => 'number',
        '#default_value' => $this->settings['mn_height_amount'],
        '#description' => t('Minimum height in px.'),
        '#attributes' => array(
          'type' => 'number',
          'step' => '1',
        ),
        '#states' => array(
          'visible' => array(
            ':input[name="style_settings[height][height_type]"]' => array('value' => 'responsive'),
          ),
        ),
      );
      $form['height']['rel_height_amount'] = array(
        '#title' => t('Relative height (vw)'),
        '#type' => 'number',
        '#default_value' => $this->settings['rel_height_amount'],
        '#description' => t('Relative height in vw (between max and min)'),
        '#attributes' => array(
          'type' => 'number',
          'step' => '1',
        ),
        '#states' => array(
          'visible' => array(
            ':input[name="style_settings[height][height_type]"]' => array('value' => 'responsive'),
          ),
        ),
      );
      $form['height']['mx_height_amount'] = array(
        '#title' => t('Maximum height (px)'),
        '#type' => 'number',
        '#default_value' => $this->settings['mx_height_amount'],
        '#description' => t('Maximum height in px.'),
        '#attributes' => array(
          'type' => 'number',
          'step' => '1',
        ),
        '#states' => array(
          'visible' => array(
            ':input[name="style_settings[height][height_type]"]' => array('value' => 'responsive'),
          ),
        ),
      );
      $form['height']['height_unit'] = array(
        '#title' => t('Unit'),
        '#type' => 'select',
        '#options' => $this->getUnitOptions(),
        '#default_value' => $this->settings['height_unit'],
        '#states' => array(
          'visible' => array(
            ':input[name="style_settings[height][height_type]"]' => array('value' => 'fixed'),
          ),
        ),
      );

      // Border settings.
      $form['border'] = array(
        '#title' => t('Border'),
        '#type' => 'fieldset',
      );
      $form['border']['border_type'] = array(
        '#type' => 'select',
        '#options' => array(
          'default' => t('Default'),
          'custom' => t('Custom'),
        ),
        '#default_value' => $this->settings['border_type'],
      );
      $form['border']['border_size'] = array(
        '#title' => t('Border Size (px)'),
        '#type' => 'number',
        '#default_value' => $this->settings['border_size'],
        '#attributes' => array(
          'type' => 'number',
          'step' => '1',
        ),
        '#states' => array(
          'visible' => array(
            ':input[name="style_settings[border][border_type]"]' => array('value' => 'custom'),
          ),
        ),
      );
      $form['border']['border_style'] = array(
        '#title' => t('Border Style'),
        '#type' => 'select',
        '#options' => $this->getBorderStyleOptions(),
        '#default_value' => $this->settings['border_style'],
        '#states' => array(
          'visible' => array(
            ':input[name="style_settings[border][border_type]"]' => array('value' => 'custom'),
          ),
        ),
      );
      $form['border']['border_color'] = array(
        '#title' => t('Border Color'),
        '#type' => 'color',
        '#default_value' => $this->settings['border_color'],
        '#states' => array(
          'visible' => array(
            ':input[name="style_settings[border][border_type]"]' => array('value' => 'custom'),
          ),
        ),
      );

      // Corner settings.
      $form['corner'] = array(
        '#title' => t('Corners'),
        '#type' => 'fieldset',
      );
      $form['corner']['corner_type'] = array(
        '#type' => 'select',
        '#options' => array(
          'default' => t('Default'),
          'round' => t('Round'),
          'square' => t('Square'),
        ),
        '#default_value' => $this->settings['corner_type'],
      );
      $form['corner']['corner_size'] = array(
        '#title' => t('Corner Size (px)'),
        '#type' => 'number',
        '#default_value' => $this->settings['corner_size'],
        '#attributes' => array(
          'type' => 'number',
          'step' => '1',
        ),
        '#states' => array(
          'visible' => array(
            ':input[name="style_settings[corner][corner_type]"]' => array('value' => 'round'),
          ),
        ),
      );

      // Shadow settings.
      $form['shadow'] = array(
        '#title' => t('Shadow'),
        '#type' => 'fieldset',
      );
      $form['shadow']['shadow_type'] = array(
        '#type' => 'select',
        '#options' => array(
          'default' => t('Default'),
          'custom' => t('Custom'),
        ),
        '#default_value' => $this->settings['shadow_type'],
      );
      $form['shadow']['shadow_size'] = array(
        '#title' => t('Shadow Size (px)'),
        '#type' => 'number',
        '#default_value' => $this->settings['shadow_size'],
        '#attributes' => array(
          'type' => 'number',
          'step' => '1',
        ),
        '#states' => array(
          'visible' => array(
            ':input[name="style_settings[shadow][shadow_type]"]' => array('value' => 'custom'),
          ),
        ),
      );
      $form['shadow']['shadow_color'] = array(
        '#title' => t('Shadow Color'),
        '#type' => 'color',
        '#default_value' => $this->settings['border_color'],
        '#states' => array(
          'visible' => array(
            ':input[name="style_settings[shadow][shadow_type]"]' => array('value' => 'custom'),
          ),
        ),
      );

      // Content padding settings.
      $form['padding'] = array(
        '#title' => t('Padding'),
        '#type' => 'fieldset',
      );

      $form['padding']['content_padding'] = array(
        '#title' => t('Custom padding'),
        '#type' => 'checkbox',
        '#default_value' => $this->settings['content_padding'],
        '#description' => t('Extra padding for this block.'),
      );

      $form['padding']['padding_top'] = array(
        '#title' => t('Padding top (px)'),
        '#type' => 'number',
        '#default_value' => $this->settings['padding_top'],
        '#attributes' => array(
          'type' => 'number',
          'step' => '1',
        ),
        '#states' => array(
          'visible' => array(
            ':input[name="style_settings[padding][content_padding]"]' => array('checked' => TRUE),
          ),
        ),
      );

      $form['padding']['padding_right'] = array(
        '#title' => t('Padding right (px)'),
        '#type' => 'number',
        '#default_value' => $this->settings['padding_right'],
        '#attributes' => array(
          'type' => 'number',
          'step' => '1',
        ),
        '#states' => array(
          'visible' => array(
            ':input[name="style_settings[padding][content_padding]"]' => array('checked' => TRUE),
          ),
        ),
      );

      $form['padding']['padding_bottom'] = array(
        '#title' => t('Padding bottom (px)'),
        '#type' => 'number',
        '#default_value' => $this->settings['padding_bottom'],
        '#attributes' => array(
          'type' => 'number',
          'step' => '1',
        ),
        '#states' => array(
          'visible' => array(
            ':input[name="style_settings[padding][content_padding]"]' => array('checked' => TRUE),
          ),
        ),
      );

      $form['padding']['padding_left'] = array(
        '#title' => t('Padding left (px)'),
        '#type' => 'number',
        '#default_value' => $this->settings['padding_left'],
        '#attributes' => array(
          'type' => 'number',
          'step' => '1',
        ),
        '#states' => array(
          'visible' => array(
            ':input[name="style_settings[padding][content_padding]"]' => array('checked' => TRUE),
          ),
        ),
      );

      // Attach form css to fix color inputs.
      $form['#attached']['css'][] = backdrop_get_path('module', 'configurable_block_style') . '/css/configurable_block_style.form.css';
    }
  }

  /**
   * Validate handler to validate the form settings.
   */
  public function formValidate($form, $form_state) {
  }

  /**
   * Submit handler for saving the form settings.
   */
  public function formSubmit($form, $form_state) {
    $this->settings['classes'] = $form_state['values']['style_settings']['classes'];

    $this->settings['content_container'] = $form_state['values']['style_settings']['content_container'];
    $this->settings['content_padding'] = $form_state['values']['style_settings']['padding']['content_padding'];
    $this->settings['padding_top'] = $form_state['values']['style_settings']['padding']['padding_top'];
    $this->settings['padding_right'] = $form_state['values']['style_settings']['padding']['padding_right'];
    $this->settings['padding_bottom'] = $form_state['values']['style_settings']['padding']['padding_bottom'];
    $this->settings['padding_left'] = $form_state['values']['style_settings']['padding']['padding_left'];

    $this->settings['color_type'] = $form_state['values']['style_settings']['colors']['color_type'];
    $this->settings['text_color'] = $form_state['values']['style_settings']['colors']['text_color'];
    $this->settings['background_color'] = $form_state['values']['style_settings']['colors']['background_color'];

    $this->settings['border_type'] = $form_state['values']['style_settings']['border']['border_type'];
    $this->settings['border_size'] = $form_state['values']['style_settings']['border']['border_size'];
    $this->settings['border_style'] = $form_state['values']['style_settings']['border']['border_style'];
    $this->settings['border_color'] = $form_state['values']['style_settings']['border']['border_color'];

    $this->settings['corner_type'] = $form_state['values']['style_settings']['corner']['corner_type'];
    $this->settings['corner_size'] = $form_state['values']['style_settings']['corner']['corner_size'];

    $this->settings['shadow_type'] = $form_state['values']['style_settings']['shadow']['shadow_type'];
    $this->settings['shadow_size'] = $form_state['values']['style_settings']['shadow']['shadow_size'];
    $this->settings['shadow_color'] = $form_state['values']['style_settings']['shadow']['shadow_color'];

    $this->settings['height_type'] = $form_state['values']['style_settings']['height']['height_type'];
    $this->settings['height_amount'] = $form_state['values']['style_settings']['height']['height_amount'];
    $this->settings['mn_height_amount'] = $form_state['values']['style_settings']['height']['mn_height_amount'];
    $this->settings['rel_height_amount'] = $form_state['values']['style_settings']['height']['rel_height_amount'];
    $this->settings['mx_height_amount'] = $form_state['values']['style_settings']['height']['mx_height_amount'];
    $this->settings['height_unit'] = $form_state['values']['style_settings']['height']['height_unit'];

    $this->settings['tint'] = $form_state['values']['style_settings']['colors']['tint'];
    $this->settings['tint_value'] = $form_state['values']['style_settings']['colors']['tint_value'];
  }

  protected function getUnitOptions() {
    return array(
      'px' => 'px',
      'em' => 'em',
      'rem' => 'rem',
      'vh' => 'vh',
      '%' => '%',
    );
  }

  protected function getBorderStyleOptions() {
    return array(
      'dashed' => t('Dashed'),
      'dotted' => t('Dotted'),
      'double' => t('Double'),
      'solid' => t('Solid'),
    );
  }
}
