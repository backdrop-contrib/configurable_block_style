# Configurable Block Style

This module provides a block style with many configuration options to allow easy
customization of the appearance and markup of your blocks — without writing any code.

## Features

### Visual Styling
- **Colors** — Set custom background and text colors, or use theme defaults
- **Tint** — Add a color tint overlay over a background color or background image
- **Height** — Set a fixed, responsive (min/max with viewport-relative scaling), or
  image-fitted height for hero blocks
- **Border** — Add a custom border with configurable size, style, and color
- **Corners** — Set rounded or square corners with a configurable radius
- **Shadow** — Add a drop shadow with configurable size and color
- **Padding** — Set custom top, right, bottom, and left padding values

### Layout & Markup
- **Content container** — Wrap block content in a `.container` div to align it with
  other layout regions
- **Wrapper tag** — Choose the HTML element for the block wrapper (DIV, ASIDE, SECTION,
  NAV, P)
- **Heading level** — Choose the HTML tag for the block title (H1–H6, DIV, P)
- **Heading classes** — Add custom CSS classes to the block title element
- **Content tag** — Choose the HTML element wrapping the block content, or remove it
  entirely
- **Content classes** — Add custom CSS classes to the content wrapper element
- **Additional CSS classes** — Add custom classes to the block wrapper

All settings sections collapse automatically when at their defaults, keeping the
configuration form compact. Sections with active customizations stay open for easy review.

## Installation

Install this module using the official Backdrop CMS instructions at
https://backdropcms.org/guide/modules.

## Instructions

1. Go to **Admin > Structure > Layouts** and select "Manage Blocks" for the layout
   you wish to edit.

2. Choose the block you wish to style and select "Configure".

3. Open the "Style" section and choose "Configurable" from the style selector.

4. Expand the settings sections you want to customize, make your choices, and click
   "Update Block".

5. Save the layout for changes to take effect.

See screenshots: https://github.com/backdrop-contrib/configurable_block_style/wiki

Video: https://youtu.be/WfuUIVzjQUg (does not include all recent features)

## Maintainers

- Joseph Flatt (hosef)
- Tim Erickson (stpaultim)

## License

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.
