<?php

/**
 * @file
 * Plugin definition.
 */

$plugin = array(
  'title' => t('Company card'),
  'description' => t('Show list of company cards.'),
  'category' => t('Gizra'),
  'hook theme' => 'dynamic_example_lesson_company_card_content_type_theme',
);

/**
 * Render callback.
 */
function dynamic_example_lesson_company_card_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->module = 'dynamic_example_lesson';
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

    if ($node->comment_count == 0) {
      $comment = t('No comments');
    }
    else {
      $comment = format_plural($node->comment_count, '1 comment', '@count comments');
    }

    $variables = array(
      'image' => $image,
      'title' => check_plain($node->title),
      'comment' => $comment,
      'time_ago' => format_interval(time() - $node->created),
    );

    $cards_item[] = theme('dynamic_example_lesson_cards_item', $variables);

  }

  $variables = array(
    'cards_item' => $cards_item,
  );

  $block->content = theme('dynamic_example_lesson_company_card', $variables);
  return $block;
}



/**
 * Edit form.
 */
function dynamic_example_lesson_company_card_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function dynamic_example_lesson_company_card_content_type_theme(&$theme, $plugin) {
  $theme['dynamic_example_lesson_company_card'] = array(
    'variables' => array(
      'cards_item' => NULL,
    ),
    'path' => $plugin['path'],
    'template' => 'company_card',
  );

  $theme['dynamic_example_lesson_cards_item'] = array(
    'variables' => array(
      'image' => NULL,
      'title' => NULL,
      'comment' => NULL,
      'time_ago' => NULL,
    ),
    'path' => $plugin['path'],
    'template' => 'company_card_item',
  );


}
