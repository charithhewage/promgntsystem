<?php
/**
 * @file
 * Theme functions for PM Task.
 */

/**
 * Provides HTML for the task node view.
 */
function theme_pmtask_view($variables) {
  $node = $variables['node'];

  $l_pos = 1; // Used to increase the link position number (see issue 814820)

  $node->content['links'] = array(
    '#prefix' => '<div class="pmlinks">',
    '#suffix' => '</div>',
    '#weight' => -25,
  );

//  $node->content['links']['expenses'] = theme('pm_link', 'pmtask', 'pmexpense', $node->nid, $l_pos++);
//  $node->content['links']['notes'] = theme('pm_link', 'pmtask', 'pmnote', $node->nid, $l_pos++);
//  $node->content['links']['tickets'] = theme('pm_link', 'pmtask', 'pmticket', $node->nid, $l_pos++);
//  $node->content['links']['timetrackings'] = theme('pm_link', 'pmtask', 'pmtimetracking', $node->nid, $l_pos++);

  // Code to create invoice auto_add link
  if (module_exists('pminvoice')) {

    $node->content['links']['auto_invoice'] = array(
      '#prefix' => variable_get('pm_icons_display', TRUE) ? '<dt id="pminvoices" class="pmcomponent">' : '<dt class="pmcomponent">',
      '#suffix' => '</dt>',
      '#markup' => theme('pminvoice_autoadd_links', array('label' => $node->nid, 'value' => $node->billable, $node->billed)),
      '#weight' => $l_pos++,
    );
  }

  $node->content['group1'] = array(
    '#prefix' => '<div class="field">',
    '#suffix' => '</div>',
    '#weight' => module_exists('content') ? content_extra_field_weight($node->type, 'group1') : -20,
  );

  $node->content['group1']['organization'] = array(
    '#prefix' => '<div class="organization">',
    '#suffix' => '</div>',
    '#markup' => theme('pm_view_item', array('label' => t('Organization'), 'value' => l($node->organization_title, 'node/' . $node->organization_nid))),
    '#weight' => 1,
  );

  $node->content['group1']['project'] = array(
    '#prefix' => '<div class="project">',
    '#suffix' => '</div>',
    '#markup' => theme('pm_view_item', array('label' => t('Project'), 'value' => l($node->project_title, 'node/' . $node->project_nid))),
    '#weight' => 2,
  );

  $node->content['group1']['stepno'] = array(
    '#prefix' => '<div class="stepno">',
    '#suffix' => '</div>',
    '#markup' => theme('pm_view_item', array('label' => t('Step no.'), 'value' => check_plain($node->stepno))),
    '#weight' => 3,
  );

  $node->content['group2'] = array(
    '#prefix' => '<div class="field">',
    '#suffix' => '</div>',
    '#weight' => module_exists('content') ? content_extra_field_weight($node->type, 'group2') : -19,
  );

  $node->content['group2']['category'] = array(
    '#prefix' => '<div class="category">',
    '#suffix' => '</div>',
    '#markup' => theme('pm_view_item', array('label' => t('Category'), 'value' => check_plain(pm_attribute_value('Task category', $node->taskcategory)))),
    '#weight' => 1,
  );

  $node->content['group2']['status'] = array(
    '#prefix' => '<div class="pm_status">',
    '#suffix' => '</div>',
    '#markup' => theme('pm_view_item', array('label' => t('Status'), 'value' => check_plain(pm_attribute_value('Task status', $node->taskstatus)))),
    '#weight' => 2,
  );

  $node->content['group2']['priority'] = array(
    '#prefix' => '<div class="priority">',
    '#suffix' => '</div>',
    '#markup' => theme('pm_view_item', array('label' => t('Priority'), 'value' => check_plain(pm_attribute_value('Task priority', $node->taskpriority)))),
    '#weight' => 3,
  );

  $node->content['group5'] = array(
    '#prefix' => '<div class="field">',
    '#suffix' => '</div>',
    '#weight' => module_exists('content') ? content_extra_field_weight($node->type, 'group5') : -16,
  );

  $node->content['group5']['assigned'] = array(
    '#prefix' => '<div class="assigned">',
    '#suffix' => '</div>',
    '#markup' => theme('pm_view_item', array('label' => t('Assigned to'), 'value' => l($node->assigned_title, 'node/' . $node->assigned_nid))),
    '#weight' => 2,
  );

  $body = field_get_items('node', $node, 'body');
    if ($body) {
      $node->content['body'] = array(
        '#prefix' => '<div class="pmbody">',
        '#suffix' => '</div>',
        '#markup' => theme('pm_view_item', array('label' => t('Description'), 'value' => $body[0]['safe_value'])),
        '#weight' => 4,
      );
    }

  return $node;
}
