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
      'color_type' => 'default',
      'background_color' => '#ffffff',
      'text_color' => '#000000',
      'height_type' => 'default',
      'height_amount' => '500',
      'height_unit' => 'px',
    );
    $this->is_region = $is_region;
  }

  /**
   * Specifies the settings form for configuring the style.
   */
  public function form(&$form, &$form_state) {
    if (!$this->is_region) {
      $form['classes'] = array(
        '#title' => t('Block classes'),
        '#type' => 'textfield',
        '#default_value' => $this->settings['classes'],
        '#description' => t('Additional classes to be added to this block.'),
      );

      // Color settings.
      $form['colors'] = array(
        '#title' => t('Colors'),
        '#type' => 'fieldset',
      );
      $form['colors']['color_type'] = array(
        '#type' => 'select',
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

    $this->settings['color_type'] = $form_state['values']['style_settings']['colors']['color_type'];
    $this->settings['text_color'] = $form_state['values']['style_settings']['colors']['text_color'];
    $this->settings['background_color'] = $form_state['values']['style_settings']['colors']['background_color'];

    $this->settings['height_type'] = $form_state['values']['style_settings']['height']['height_type'];
    $this->settings['height_amount'] = $form_state['values']['style_settings']['height']['height_amount'];
    $this->settings['height_unit'] = $form_state['values']['style_settings']['height']['height_unit'];
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
}
