<?php

/**
 * @file
 * Plugin definition.
 */

$plugin = array(
  'title' => t('Cards'),
  'description' => t('Show the recent cards.'),
  'category' => t('Dynamic example'),
  'hook theme' => 'dynamic_example_homepage_cards_content_type_theme',
);

/**
 * Render callback.
 */
function dynamic_example_homepage_cards_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->module = 'dynamic_example_homepage';
  $block->title = '';


  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'company')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->propertyOrderBy('nid', 'DESC')
    ->range(0, 3)
    ->execute();

  if (empty($result['node'])) {
    return;
  }

  // Holds the cards Html.
  $cards_item = array();

  $nids = array_keys($result['node']);

  foreach (node_load_multiple($nids) as $node) {

    $wrapper = entity_metadata_wrapper('node', $node);
    $image = $wrapper->field_company_logo->value();

    $image = file_create_url($image['uri']);
    $comment = $node->comment_count ? format_plural($node->comment_count, '1 comment', '@count comments') : t('No comments');

    $variables = array(
      'image' => $image,
      'title' => check_plain($node->title),
      'comment' => $comment,
      'time_ago' => format_interval($node->created)
    );

    $cards_item[] = theme('dynamic_example_homepage_cards_item', $variables);
  }

  $variables = array(
    'cards_item' => $cards_item,
  );

  $block->content = theme('dynamic_example_homepage_cards', $variables);
  return $block;
}

/**
 * Edit form.
 */
function dynamic_example_homepage_cards_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function dynamic_example_homepage_cards_content_type_theme(&$theme, $plugin) {
  $theme['dynamic_example_homepage_cards'] = array(
    'variables' => array(
      'cards_item' => NULL,
    ),
    'path' => $plugin['path'],
    'template' => 'cards',
  );

  $theme['dynamic_example_homepage_cards_item'] = array(
    'variables' => array(
      'image' => NULL,
      'title' => NULL,
      'comment' => NULL,
      'time_ago' => NULL,
    ),
    'path' => $plugin['path'],
    'template' => 'cards_item',
  );

}
