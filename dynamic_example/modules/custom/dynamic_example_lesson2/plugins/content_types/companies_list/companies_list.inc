<?php

/**
 * @file
 * Plugin definition.
 */

$plugin = array(
  'title' => t('Companies list'),
  'description' => t('Show a list of recent companies.'),
  'category' => t('Gizra'),
  'hook theme' => 'dynamic_example_lesson2_companies_list_content_type_theme',
);

/**
 * Render callback.
 */
function dynamic_example_lesson2_companies_list_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->module = 'dynamic_example_lesson2';
  $block->title = '';



  $block->content = theme('dynamic_example_lesson2_companies_list');
  return $block;
}

/**
 * Edit form.
 */
function dynamic_example_lesson2_companies_list_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function dynamic_example_lesson2_companies_list_content_type_theme(&$theme, $plugin) {
  $theme['dynamic_example_lesson2_companies_list'] = array(
    'variables' => array(
      'companies_list_item' => NULL,  
    ),
    'path' => $plugin['path'],
    'template' => 'companies_list',
  );

  $theme['dynamic_example_lesson2_companies_list_item'] = array(
    'variables' => array(
      'title' => NULL,
      'url' => NULL,
      'image' => NULL,
    ),
    'path' => $plugin['path'],
    'template' => 'companies_list_item',
  );


}
