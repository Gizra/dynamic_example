<?php
/**
 * @file
 * dynamic_example_message.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function dynamic_example_message_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function dynamic_example_message_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_message_type().
 */
function dynamic_example_message_default_message_type() {
  $items = array();
  $items['dynamic_example_insert_comment'] = entity_import('message_type', '{
    "name" : "dynamic_example_insert_comment",
    "description" : "Dynamic Example Insert Comment",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "he",
    "arguments" : null,
    "message_text" : {
      "en" : [
        {
          "value" : "A new comment on a post is waiting for your approval.\\n[message:field-comment-ref:author:name] commented @{message:field-comment-ref:title} on \\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003E[message:field-node-ref:title]\\u003C\\/a\\u003E.",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EA new comment on a post is waiting for your approval.\\u003Cbr \\/\\u003E\\n[message:field-comment-ref:author:name] commented @{message:field-comment-ref:title} on \\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003E[message:field-node-ref:title]\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\n"
        }
      ],
      "he" : [
        {
          "value" : "\\u05d4\\u05e2\\u05e8\\u05d4 \\u05d7\\u05d3\\u05e9\\u05d4 \\u05de\\u05de\\u05ea\\u05d9\\u05e0\\u05d4 \\u05dc\\u05d0\\u05d9\\u05e9\\u05d5\\u05e8\\u05da.\\r\\n[message:field-comment-ref:author:name] \\u05d4\\u05d5\\u05e1\\u05d9\\u05e3 \\u05d0\\u05ea \\u05d4\\u05d4\\u05e2\\u05e8\\u05d4 @{message:field-comment-ref:title} \\u05e2\\u05dc \\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003E[message:field-node-ref:title]\\u003C\\/a\\u003E.",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E\\u05d4\\u05e2\\u05e8\\u05d4 \\u05d7\\u05d3\\u05e9\\u05d4 \\u05de\\u05de\\u05ea\\u05d9\\u05e0\\u05d4 \\u05dc\\u05d0\\u05d9\\u05e9\\u05d5\\u05e8\\u05da.\\u003Cbr \\/\\u003E\\n[message:field-comment-ref:author:name] \\u05d4\\u05d5\\u05e1\\u05d9\\u05e3 \\u05d0\\u05ea \\u05d4\\u05d4\\u05e2\\u05e8\\u05d4 @{message:field-comment-ref:title} \\u05e2\\u05dc \\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003E[message:field-node-ref:title]\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\n"
        }
      ],
      "und" : [
        {
          "value" : "A new comment on a post is waiting for your approval.\\r\\n[message:field-comment-ref:author:name] commented [message:field-comment-ref:title] on [message:field-node-ref:title].",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EA new comment on a post is waiting for your approval.\\u003Cbr \\/\\u003E\\n[message:field-comment-ref:author:name] commented [message:field-comment-ref:title] on [message:field-node-ref:title].\\u003C\\/p\\u003E\\n"
        }
      ]
    }
  }');
  return $items;
}
