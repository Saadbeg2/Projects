document.addEventListener('DOMContentLoaded', (event) => {
    // Smooth scroll for anchor links
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', function (e) {
            e.preventDefault();
            document.querySelector(this.getAttribute('href')).scrollIntoView({
                behavior: 'smooth'
            });
        });
    });

    // Function to check screen size and display overlay
    function checkScreenSize() {
        if (window.innerWidth < 950) { // Adjust the width as needed
            document.getElementById('overlay').style.display = 'flex';
        } else {
            document.getElementById('overlay').style.display = 'none';
        }
    }

    // Event listeners for resize and load
    window.addEventListener('resize', checkScreenSize);
    window.addEventListener('load', checkScreenSize);

    // Initial check
    checkScreenSize();
});
