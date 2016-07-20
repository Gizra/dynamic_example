<?php

/**
 * @file
 * Plugin definition.
 */

$plugin = array(
  'title' => t('Companies'),
  'description' => t('Show the recent companies.'),
  'category' => t('Dynamic example'),
  'hook theme' => 'dynamic_example_homepage_companies_content_type_theme',
);

/**
 * Render callback.
 */
function dynamic_example_homepage_companies_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->module = 'dynamic_example_homepage';
  $block->title = '';


  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'company')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->propertyOrderBy('nid', 'DESC')
    ->range(0, 5)
    ->execute();

  if (empty($result['node'])) {
    return;
  }

  $companies = array();

  $nids = array_keys($result['node']);
  foreach (node_load_multiple($nids) as $node) {

    $wrapper = entity_metadata_wrapper('node', $node);
    $image = $wrapper->field_company_logo->value();

    $image = file_create_url($image['uri']);

    $variables = array(
      'image' => $image,
      'title' => check_plain($node->title),
      'link' => url('node/' . $node->nid),
    );

    $companies[] = theme('dynamic_example_homepage_companies_item', $variables);
  }

  $variables = array(
    'companies' => $companies,
  );

  $block->content = theme('dynamic_example_homepage_companies', $variables);
  return $block;
}

/**
 * Edit form.
 */
function dynamic_example_homepage_companies_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function dynamic_example_homepage_companies_content_type_theme(&$theme, $plugin) {
  $theme['dynamic_example_homepage_companies'] = array(
    'variables' => array(
      'companies' => NULL,
    ),
    'path' => $plugin['path'],
    'template' => 'companies',
  );

  $theme['dynamic_example_homepage_companies_item'] = array(
    'variables' => array(
      'image' => NULL,
      'title' => NULL,
      'link' => NULL,
    ),
    'path' => $plugin['path'],
    'template' => 'companies_item',
  );

}
