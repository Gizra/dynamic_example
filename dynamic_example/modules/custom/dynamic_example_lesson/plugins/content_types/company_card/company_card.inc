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


  $block->content = check_plain($node->title);
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
    ),
    'path' => $plugin['path'],
    'template' => 'company_card',
  );

}
