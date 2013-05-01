<?php

/**
 * @file
 * TODO.
 */

function user_disk_quota_role_form($form, &$form_state) {
  $roles = user_roles();
  $form = array();
  $form['roles'] = array(
    '#type' => 'fieldset',
    '#collapsed' => FALSE,
    '#collapsible' => FALSE,
    '#title' => t('Roles'),
  );
  foreach ($roles as $rid => $role) {
    $default = variable_get('user_disk_quota_role_' . $rid, '');
    if (!empty($default)) {
      $default = format_size($default);
    }
    $form['roles']['user_disk_quota_role_' . $rid] = array(
      '#type' => 'textfield',
      '#title' => $role,
      '#default_value' => $default,
      '#element_validate' => array('_user_disk_quota_form_quota_validate'),
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

function user_disk_quota_role_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $strlenght = strlen('user_disk_quota_role_');
  foreach ($values as $key => $value) {
    if (substr($key, 0, $strlenght) == 'user_disk_quota_role_') {
      $value = parse_size(check_plain($value));
      if($value == 0){
        $value = '';
      }
      variable_set($key, $value);
    }
  }
}