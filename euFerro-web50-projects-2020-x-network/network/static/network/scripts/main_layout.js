
document.addEventListener("DOMContentLoaded", () => {

    sidebar = document.querySelector("#side-bar");
    main_body = document.querySelector(".body");

    main_body.style.left = sidebar.offsetWidth + 'px';

})
