document.addEventListener('DOMContentLoaded', function() {
  console.log('Script loaded for block');
  var blockTitles = document.querySelectorAll('.block-title');
  console.log('Number of block titles found:', blockTitles.length);
  blockTitles.forEach(function(blockTitle) {
    var blockId = blockTitle.getAttribute('id').replace('block-title-', '');
    var blockContent = document.querySelector('#block-content-' + blockId);
    var toggleIcon = document.querySelector('#toggle-icon-' + blockId);
    console.log('Block title:', blockTitle);
    console.log('Block content:', blockContent);
    console.log('Toggle icon:', toggleIcon);
    if (blockTitle && blockContent && toggleIcon) {
      // Set initial state
      blockContent.style.display = 'block';
      toggleIcon.innerHTML = '&#9660;'; // Down arrow

      blockTitle.addEventListener('click', function() {
        if (blockContent.style.display === 'none') {
          blockContent.style.display = 'block';
          toggleIcon.innerHTML = '&#9660;'; // Down arrow
        } else {
          blockContent.style.display = 'none';
          toggleIcon.innerHTML = '&#9654;'; // Right arrow
        }
      });
    }
  });
}); 