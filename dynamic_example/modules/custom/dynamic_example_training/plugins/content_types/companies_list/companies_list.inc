<?php

/**
 * @file
 * Plugin definition.
 */

$plugin = array(
    'title' => t('Companies list'),
    'description' => t('Show a list of recent companies.'),
    'category' => t('Training'),
    'hook theme' => 'dynamic_example_training_companies_list_content_type_theme',
);

/**
 * Render callback.
 */
function dynamic_example_training_companies_list_content_type_render($subtype, $conf, $args, $context) {
    $block = new stdClass();
    $block->module = 'dynamic_example_training';
    $block->title = '';

    $companies_list_item = array();

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

        $companies_list_item[] = theme('dynamic_example_training_companies_list_item', $variables);
    }

    $variables = array(
      'companies_list_item' => $companies_list_item,
    );


    $block->content = theme('dynamic_example_training_companies_list', array());
    return $block;
}

/**
 * Edit form.
 */
function dynamic_example_training_companies_list_content_type_edit_form($form, &$form_state) {
    return $form;
}

/**
 * Delegated hook_theme().
 */
function dynamic_example_training_companies_list_content_type_theme(&$theme, $plugin) {
    $theme['dynamic_example_training_companies_list'] = array(
        'variables' => array(
            'companies_list_item' => NULL,

        ),
        'path' => $plugin['path'],
        'template' => 'companies_list',
    );

    $theme['dynamic_example_training_companies_list_item'] = array(
        'variables' => array(
            'title' => NULL,
            'url' => NULL,
            'image' => NULL,

        ),
        'path' => $plugin['path'],
        'template' => 'companies_list_item',
    );


}
