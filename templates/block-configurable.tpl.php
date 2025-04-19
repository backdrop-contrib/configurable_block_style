<?php
/**
 * @file
 * Template for outputting the default block styling within a Layout.
 *
 * Variables available:
 * - $classes: Array of classes that should be displayed on the block's wrapper.
 * - $title: The title of the block.
 * - $title_prefix/$title_suffix: A prefix and suffix for the title tag. This
 *   is important to print out as administrative links to edit this block are
 *   printed in these variables.
 * - $content: The actual content of the block.
 */
?>
<div class="<?php print implode(' ', $classes);?>" <?php print backdrop_attributes($attributes);
?>>
  <?php if (!empty($content_container)):?>
  <div class="container">
  <?php endif;?>
    <?php print render($title_prefix);?>
    
    <?php if ($title):?>
      
    <?php if ($make_title_link == 1): ?>

    <h2 id="block-title-<?php print $block_id; ?>" class="block-title" style="cursor: pointer;">
      <?php if ($make_title_link): ?>
        <a href="<?php print $block_title_link; ?>"><?php print $title; ?></a>
      <?php else: ?>
        <?php print $title; ?>
      <?php endif; ?>
      <?php if ($collapsible && $show_caret): ?>
        <span id="toggle-icon-<?php print $block_id; ?>" style="font-size: 0.4em; vertical-align: middle; margin-left: 5px;">&#9660;</span>
      <?php endif; ?>
    </h2>
  
    <?php else: ?>
      
    <h2 id="block-title-<?php print $block_id; ?>" class="block-title"><?php print $title;?>
    <?php if ($collapsible && $show_caret): ?>
      <span id="toggle-icon-<?php print $block_id; ?>" style="font-size: 0.4em; vertical-align: middle; margin-left: 5px;">&#9660;</span>
    <?php endif; ?></h2>
    <?php endif; ?>
    <?php endif;?>
    
    <?php print render($title_suffix);?>
    <div id="block-content-<?php print $block_id; ?>" class="block-content">
      <?php print render($content);?>
    </div>

    <?php if ($collapsible): ?>
    <script src="/<?php print backdrop_get_path('module', 'configurable_block_style'); ?>/js/block-toggle.js"></script>
    <?php endif; ?>
  <?php if (!empty($content_container)):?>
  </div>
  <?php endif;?>
</div>
