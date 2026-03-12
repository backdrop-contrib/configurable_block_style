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
 * - $collapsible: Whether the block content can be toggled open/closed.
 * - $make_title_link: Whether the block title should be rendered as a link.
 * - $block_title_link: URL for the block title link.
 * - $content_tag: The HTML tag to use around the block content.
 * - $content_attributes: Attributes (including classes) for the content element.
 * - $block_id: The block UUID, used to associate the toggle with the content.
 * - $content: The actual content of the block.
 */
?>
<<?php print $wrapper_tag; ?> class="<?php print implode(' ', $classes); ?>"<?php print backdrop_attributes($attributes); ?>>
  <?php if (!empty($content_container)):?>
  <div class="container">
  <?php endif;?>
    <?php print render($title_prefix);?>
    <?php if ($title):?>
    <<?php print $title_tag; ?><?php if ($collapsible): ?> id="block-title-<?php print $block_id; ?>"<?php endif; ?><?php print backdrop_attributes($title_attributes); ?>>
      <?php if ($collapsible): ?>
        <?php if ($make_title_link): ?>
          <span class="block-title-toggle">
            <a href="<?php print $block_title_link; ?>"><?php print $title; ?></a>
            <span class="toggle-caret" role="button" tabindex="0" aria-controls="block-content-<?php print $block_id; ?>" aria-expanded="true">&#9654;</span>
          </span>
        <?php else: ?>
          <span class="block-title-toggle" role="button" tabindex="0" aria-controls="block-content-<?php print $block_id; ?>" aria-expanded="true">
            <?php print $title; ?>
            <span class="toggle-caret">&#9654;</span>
          </span>
        <?php endif; ?>
      <?php elseif ($make_title_link): ?>
        <a href="<?php print $block_title_link; ?>"><?php print $title; ?></a>
      <?php else: ?>
        <?php print $title; ?>
      <?php endif; ?>
    </<?php print $title_tag; ?>>
    <?php endif;?>
    <?php print render($title_suffix);?>
    <?php
    // Use the configured content tag, falling back to div when collapsible
    // so the JS toggle target always exists.
    $effective_content_tag = !empty($content_tag) ? $content_tag : ($collapsible ? 'div' : '');
    ?>
    <?php if ($effective_content_tag): ?>
    <<?php print $effective_content_tag; ?><?php if ($collapsible): ?> id="block-content-<?php print $block_id; ?>"<?php endif; ?><?php print backdrop_attributes($content_attributes); ?>>
    <?php endif; ?>
      <?php print render($content);?>
    <?php if ($effective_content_tag): ?>
    </<?php print $effective_content_tag; ?>>
    <?php endif; ?>
  <?php if (!empty($content_container)):?>
  </div>
  <?php endif;?>
</<?php print $wrapper_tag; ?>>
