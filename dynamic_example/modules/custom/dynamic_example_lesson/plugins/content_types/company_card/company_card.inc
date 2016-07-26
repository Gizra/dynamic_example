<?php

/**
 * @file
 * Plugin definition.
 */

$plugin = array(
  'title' => t('Company card'),
  'description' => t('Show a company node as card.'),
  'category' => t('Gizra'),
  'required context' => new ctools_context_required(t('Company node'), 'node'),
  'hook theme' => 'dynamic_example_lesson_company_card_content_type_theme',
);

/**
 * Render callback.
 */
function dynamic_example_lesson_company_card_content_type_render($subtype, $conf, $args, $context) {
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

  // Holds the cards Html.
  $cards = array();

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

    );

    $cards[] = theme('dynamic_example_lesson_company_card', $variables);
  }


  $variables = array(
      'cards' => $cards,

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
      'company_card' => NULL,
    ),
    'path' => $plugin['path'],
    'template' => 'company_card',
  );

}
