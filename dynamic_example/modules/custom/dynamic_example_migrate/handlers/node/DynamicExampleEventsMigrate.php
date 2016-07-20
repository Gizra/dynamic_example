<?php

/**
 * @file
 * Contains \DynamicExampleEventsMigrate.
 */

class DynamicExampleEventsMigrate extends \DynamicExampleMigrateBase {

  public $entityType = 'node';
  public $bundle = 'event';

  public $fields = array(
    '_location',
    '_company',
    '_author',
  );

  public $dependencies = array(
    'DynamicExampleCompaniesMigrate',
    'DynamicExampleUsersMigrate',
  );


  public function __construct($arguments) {
    parent::__construct($arguments);

    $this
      ->addFieldMapping(OG_AUDIENCE_FIELD, '_company')
      ->sourceMigration('DynamicExampleCompaniesMigrate');

    $this
      ->addFieldMapping('uid', '_author')
      ->sourceMigration('DynamicExampleUsersMigrate');
  }

  /**
   * Map location field.
   *
   * @todo: Move to value callback.
   */
  public function prepare($entity, $row) {
    list($lat, $lng) = explode('|', $row->_location);
    $wrapper = entity_metadata_wrapper('node', $entity);
    $values = array(
      'lat' => $lat,
      'lng' => $lng,
    );
    $wrapper->field_location->set($values);
  }
}
