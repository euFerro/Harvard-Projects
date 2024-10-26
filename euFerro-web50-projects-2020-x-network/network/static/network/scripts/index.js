
document.addEventListener('DOMContentLoaded', () => {

    // Default homepage display
    document.querySelector("#all-posts-div").style.display = "flex";
    document.querySelector("#all-posts-div").style.flexDirection = "column";
    document.querySelector("#following-posts-div").style.display = "none";
    document.querySelector("#following-posts-div").style.flexDirection = "column";
    document.querySelector("#blue-bar-all").style.display = "block";
    document.querySelector("#blue-bar-following").style.display = "none";

    // Main header resize function
    window.addEventListener('resize', resize_header);

    // Initial header offset and width
    post_div = document.querySelector(".post-div");
    header = document.querySelector(".home-header");
    post_div.style.top = header.offsetHeight + 'px';
    header.style.width = post_div.offsetWidth + 'px';

    document.querySelector("#simple-post-form").addEventListener("submit", send_post);
    document.querySelector("#AllPosts").onclick = get_all_posts;
    document.querySelector("#FollowingPosts").onclick = get_following_posts;

})


function send_post(event) {
    event.preventDefault();
    
    // Clear notice msgs
    msg_div = document.getElementById("post-header-msg-div");
    children = msg_div.childNodes;
    children.forEach(child => {
        child.remove();
    });

    // Get inputs
    userInput = document.getElementById("user-header-input");
    textInput = document.getElementById("text-header-input");
    fileInput = document.getElementById("image-header-input");

    // Check if text input is empty
    if (textInput.value.length == 0) {
        error = document.createElement('p');
        error.innerHTML = "no text was provided";
        error.style.color = "#ddaa00";
        document.getElementById("post-header-msg-div").append(error);
        return false;
    }
    const user_id = userInput.value;
    const text = textInput.value;
    const file = fileInput.files[0];

    formData = new FormData();
    formData.append('user', user_id);
    formData.append('text', text);
    formData.append('img', file);

    fetch("/post", {
        "method": "POST",
        "body": formData,
    })
    .then(response => response.json())
    .then(response => {

        if (response.error) {
            error = document.createElement('p');
            error.innerHTML = response.error;
            error.style.color = "red";
            document.querySelector("#post-header-msg-div").append(error);
        }
        if (response.ok) {
            ok = document.createElement('p');
            ok.innerHTML = response.ok;
            ok.style.color = "aqua";
            document.querySelector("#post-header-msg-div").append(ok);
            document.querySelector("#text-header-input").value = "";
            location.reload();
        }
        console.log(response);
    })

    // Prevent default behavior
    return false;
}

function resize_header() {
    header = document.querySelector(".home-header");
    post_div = document.querySelector(".post-div");
    header.style.width = post_div.offsetWidth + 'px';
}

function get_all_posts() {
    console.log("GET ALL POSTS");

    fetch("/posts", {
        "method": "GET"
    })
    .then(response => {
        if (response.error) {
            console.log(response.error);
        }
        if (response.ok) {
            console.log(response.ok);
        }
        
    });
    return false;
}

function get_following_posts() {
    console.log("GET FOLLOWING POSTS");

    fetch("/posts", {
        "method": "GET"
    })
    .then(() => {

    });
    return false;
}