
document.addEventListener("DOMContentLoaded", () => {

    like_divs = document.querySelectorAll('.like-div');
    like_divs.forEach(element => {
        element.onmouseover = style_like_btn;
        element.onmouseout = unstyle_like_btn;
    });

    comment_divs = document.querySelectorAll('.comment-div');
    comment_divs.forEach(element => {
        element.onmouseover = style_comment_btn;
        element.onmouseout = unstyle_comment_btn;
    });

})


function style_like_btn() {
    this.style.color = "#ee0055";
    this.childNodes[1].style.backgroundColor = "#330011";
    this.childNodes[1].childNodes[1].childNodes[1].style.fill = "#ee0055";
}

function unstyle_like_btn() {
    this.style.color = "#777";
    this.childNodes[1].style.backgroundColor = "transparent";
    this.childNodes[1].childNodes[1].childNodes[1].style.fill = "#777";
}

function style_comment_btn() {
    this.style.color = "#00ffff";
    this.childNodes[1].style.backgroundColor = "#003333";
    this.childNodes[1].childNodes[1].childNodes[1].childNodes[1].childNodes[1].style.fill = "#00ffff";
}

function unstyle_comment_btn() {
    this.style.color = "#777";
    this.childNodes[1].style.backgroundColor = "transparent";
    this.childNodes[1].childNodes[1].childNodes[1].childNodes[1].childNodes[1].style.fill = "#777";
}