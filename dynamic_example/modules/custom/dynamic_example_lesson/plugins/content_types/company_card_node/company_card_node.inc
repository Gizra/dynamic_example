<?php

/**
 * @file
 * Plugin definition.
 */

$plugin = array(
  'title' => t('Company card node'),
  'description' => t('Show a company node as card.'),
  'category' => t('Gizra'),
  'required context' => new ctools_context_required(t('Company node'), 'node'),
  'hook theme' => 'dynamic_example_lesson_company_card_node_content_type_theme',
);

/**
 * Render callback.
 */
function dynamic_example_lesson_company_card_node_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->module = 'dynamic_example_lesson';
  $block->title = '';

  if (empty($context->data)) {
    return;
  }

  $node = $context->data;

  if ($node->type != 'company') {
    throw new Exception('Node context must be a company.');
  }

  $wrapper = entity_metadata_wrapper('node', $node);
  $image = $wrapper->field_company_logo->value();

  $image = file_create_url($image['uri']);

  $comment = $node->comment_count ? format_plural($node->comment_count, '1 comment', '@count comments') : t('No comments');

  $variables = array(
      'title' => check_plain($node->title),
      'image' => $image,
      'time_ago' => format_interval(time() - $node->created),
      'comment' => $comment,
  );


  $block->content = theme('dynamic_example_lesson_company_card_node', $variables);
  return $block;
}

/**
 * Edit form.
 */
function dynamic_example_lesson_company_card_node_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function dynamic_example_lesson_company_card_node_content_type_theme(&$theme, $plugin) {
  $theme['dynamic_example_lesson_company_card_node'] = array(
    'variables' => array(
      'title' => NULL,
      'image' => NULL,
      'time_ago' => NULL,
      'comment' => NULL,
    ),
    'path' => $plugin['path'],
    'template' => 'company_card_node',
  );

}
