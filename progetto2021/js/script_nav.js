/* * * * * * Script per la navabar * * * * * */
const header = document.querySelector('header');

document.addEventListener('scroll', () => {
	var scroll_position = window.scrollY;
	if (scroll_position > 90) {
		header.style.backgroundColor = 'rgba(19,19,19,0.93)';
	} else {
		header.style.backgroundColor = 'transparent';
	}
});

