<?php
/**
 * @file
 * Template for outputting the configurable block styling within a Layout.
 *
 * Variables available:
 * - $wrapper_tag: The HTML tag to use for the block wrapper element.
 * - $classes: Array of classes that should be displayed on the block's wrapper.
 * - $attributes: Attributes (including inline styles) for the block wrapper.
 * - $content_container: Whether to add a .container div around the content.
 * - $title: The title of the block.
 * - $title_prefix/$title_suffix: Prefix and suffix for the title tag (admin links).
 * - $title_tag: The HTML tag to use for the block title.
 * - $title_attributes: Attributes (including classes) for the title element.
 * - $content_tag: The HTML tag to use around the block content.
 * - $content_attributes: Attributes (including classes) for the content element.
 * - $content: The actual content of the block.
 */
?>
<<?php print $wrapper_tag; ?> class="<?php print implode(' ', $classes); ?>"<?php print backdrop_attributes($attributes); ?>>
  <?php if (!empty($content_container)):?>
  <div class="container">
  <?php endif;?>
    <?php print render($title_prefix);?>
    <?php if ($title):?>
    <<?php print $title_tag; ?><?php print backdrop_attributes($title_attributes); ?>><?php print $title; ?></<?php print $title_tag; ?>>
    <?php endif;?>
    <?php print render($title_suffix);?>
    <?php if ($content_tag): ?>
    <<?php print $content_tag; ?><?php print backdrop_attributes($content_attributes); ?>>
    <?php endif; ?>
      <?php print render($content);?>
    <?php if ($content_tag): ?>
    </<?php print $content_tag; ?>>
    <?php endif; ?>
  <?php if (!empty($content_container)):?>
  </div>
  <?php endif;?>
</<?php print $wrapper_tag; ?>>
