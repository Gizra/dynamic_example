<?php

/**
 * @file
 * Plugin definition.
 */

$plugin = array(
  'title' => t('Companies list'),
  'description' => t('Show a list of recent companies.'),
  'category' => t('Gizra'),
  'hook theme' => 'dynamic_example_lesson_companies_list_content_type_theme',
);

/**
 * Render callback.
 */
function dynamic_example_lesson_companies_list_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->module = 'dynamic_example_lesson';
  $block->title = '';

  $companies_item = array();

  $nodes = array();

  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'company')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->propertyOrderBy('nid', 'DESC')
    ->range(0, 5)
    ->execute();

  if (empty($result['node'])) {
    // No companies.
    return;
  }

  $nids = array_keys($result['node']);
  $nodes = node_load_multiple($nids);

  foreach ($nodes as $node) {
    $variables = array(
      'title' => check_plain($node->title),
      'url' => url('node/' . $node->nid),
      'image' => 'http://placehold.it/150x150',
    );

    $companies_item[] = theme('dynamic_example_lesson_companies_item', $variables);
  }

  $variables = array(
    'companies_item' => $companies_item,
  );


  $block->content = theme('dynamic_example_lesson_companies_list', $variables);
  return $block;
}

/**
 * Edit form.
 */
function dynamic_example_lesson_companies_list_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function dynamic_example_lesson_companies_list_content_type_theme(&$theme, $plugin) {
  $theme['dynamic_example_lesson_companies_list'] = array(
    'variables' => array(
      'companies_item' => NULL,
    ),
    'path' => $plugin['path'],
    'template' => 'companies_list',
  );

  $theme['dynamic_example_lesson_companies_item'] = array(
    'variables' => array(
      'title' => NULL,
      'url' => NULL,
      'image' => NULL,
    ),
    'path' => $plugin['path'],
    'template' => 'companies_item',
  );

}
