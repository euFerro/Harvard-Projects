import "./PostForm.css";
import { useState, useEffect } from "react";
import Post from "./Post";


function PostForm({user, title, placeholder, btn_name, post}) {
    const [new_posts, setNewPost] = useState([]);

    if (btn_name === undefined) {
        btn_name = 'Post';
    }

    if (title === undefined) {
        title = 'New Post';
    }
    if (placeholder === undefined) {
        placeholder = 'What is happening ?';
    }

    function clearTextInput() {
        const textInput = document.getElementById("text-input");
        textInput.value = '';
    }

    function clearMsgs() {
        const msgDiv = document.querySelector("#post-header-msg-div");
        msgDiv.innerHTML = '';
    }

    function loadImg(event) {
        showFormImage();
        const target = event.target;
        const imageDiv = document.querySelector('.post-img-div');
        const image = document.getElementById('post-img');
        const files = target.files;

        // If there is FileReader support in the browser

        if (FileReader && files && files.length) {
            var fr = new FileReader();
            fr.onload = function () {
                image.src = fr.result;
            }
            fr.readAsDataURL(files[0]);
            imageDiv.style.display = 'block';
        } else {
            alert('Browser doesn\'t support file upload');
        }
    }

    function unloadImg() {
        const image_input = document.querySelector('#image-input');
        image_input.value = '';
        hideFormImage();
    }

    function resizeTextarea() {
        const textarea = document.querySelector('#text-input');
        textarea.style.height = textarea.scrollHeight + 'px';
    }

    function hideFormImage() {
        const imageDiv = document.querySelector(".img-div");
        const image = document.querySelector('#post-img');
        const xbtn = document.querySelector(".x-btn");
        image.style.display = 'none';
        imageDiv.style.display = 'none';
        xbtn.style.display = 'none';
    }

    function showFormImage() {
        const imageDiv = document.querySelector(".img-div");
        const image = document.querySelector('#post-img');
        const xbtn = document.querySelector(".x-btn");
        image.style.display = 'block';
        imageDiv.style.display = 'block';
        xbtn.style.display = 'flex';
    }

    function playLoadingAnimation() {
        // Play loading animation
        const loading_bar = document.querySelector('.loading-animation');
        const new_post_div  =document.querySelector(".post-animation");
        loading_bar.style.display = 'block';
        new_post_div.style.display = 'block';
        loading_bar.style.animationPlayState = 'running';
        new_post_div.style.animationPlayState = 'running';
        setTimeout(() => {
            loading_bar.style.display = 'none';
            loading_bar.style.animationPlayState = 'paused';
        }, 1500);
        setTimeout(() => {
            new_post_div.style.animationPlayState = 'paused';
        }, 1470);
    }

    function send_post(event) {
        event.preventDefault();
        
        // Clear notice msgs
        const msg_div = document.getElementById("post-header-msg-div");
        const children = msg_div.childNodes;
        children.forEach(child => {
            child.remove();
        });

        // Get inputs
        const userInput = document.getElementById("user-input");
        const textInput = document.getElementById("text-input");
        const fileInput = document.getElementById("image-input");

        // Check if text input is empty
        if (textInput.value.length === 0) {
            const error = document.createElement('p');
            error.innerHTML = "no text was provided";
            error.style.color = "#ddaa00";
            document.getElementById("post-header-msg-div").append(error);
            userInput.style.borderBottom = "#ddaa00";
            return false;
        }
        const user_id = userInput.value;
        const text = textInput.value;
        const file = fileInput.files[0];

        const formData = new FormData();
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
                const error = document.createElement('p');
                error.innerHTML = response.error;
                error.style.color = "red";
                document.querySelector("#post-header-msg-div").append(error);
                return false;
            }
            if (response.ok) {
                const ok = document.createElement('p');
                ok.innerHTML = response.ok;
                ok.style.color = "aqua";
                document.querySelector("#post-header-msg-div").append(ok);
                document.querySelector("#text-input").value = "";
                if (fileInput.value !== '') {
                    unloadImg();
                }
                clearTextInput();
                clearMsgs();

                // Add new created post to the view
                setNewPost(new_posts.concat([response.post]));

                // Play loading animation
                playLoadingAnimation();
                return false;
            }
            console.log(response);
        })

        // Prevent default behavior
        return false;
    }

    useEffect(() => {
        hideFormImage();
        if (post !== undefined) {
            const textInput = document.getElementById("text-input");
            textInput.value = post.text;

            if (post.image_url !== '' && post.image_url !== undefined && post.image_url !== null) {
                console.log(post.image_url);
                const img = document.getElementById("post-img");
                img.src = post.image_url;
                showFormImage();
            }
        }
        resizeTextarea();
        const form = document.querySelector("#simple-post-form");
        const textarea = document.querySelector('#text-input');
        form.addEventListener("submit", send_post);
        textarea.addEventListener("input", resizeTextarea);
    }, [])

    
    return(

        <>
            <div className="post-div">

                <div className="post">

                    <div className="post-profile-div">
                        <img
                            className="profile-pic"
                            src={user.profile_picture_url}
                            alt=""
                        />
                    </div>

                    <div className="post-content">

                        <div className="post-header">
                            <span className="post-fullname">{title}</span>
                            <span className="post-info">@{user.username}</span>
                            {post !== undefined ? (
                                <span className="post-info">
                                    {post.created_at.hour}:{post.created_at.minute} {post.created_at.month}/{post.created_at.day}/{post.created_at.year} 
                                </span>
                            ): (
                                <></>
                            )}
                        </div>

                        <div className="post-form-div">
                            <form id="simple-post-form">

                                <input id="user-input" type="hidden" value={user.user_id}/>
                                <textarea className="text-input" id="text-input" autoComplete="off" name="text" type="text" placeholder={placeholder}/>
                          
                                <div className="post-img-div img-div">
                                    
                                    <div onClick={unloadImg} className="x-btn">
                                        <svg width="16px" height="16px" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
                                            <path d="M20.7457 3.32851C20.3552 2.93798 19.722 2.93798 19.3315 3.32851L12.0371 10.6229L4.74275 3.32851C4.35223 2.93798 3.71906 2.93798 3.32854 3.32851C2.93801 3.71903 2.93801 4.3522 3.32854 4.74272L10.6229 12.0371L3.32856 19.3314C2.93803 19.722 2.93803 20.3551 3.32856 20.7457C3.71908 21.1362 4.35225 21.1362 4.74277 20.7457L12.0371 13.4513L19.3315 20.7457C19.722 21.1362 20.3552 21.1362 20.7457 20.7457C21.1362 20.3551 21.1362 19.722 20.7457 19.3315L13.4513 12.0371L20.7457 4.74272C21.1362 4.3522 21.1362 3.71903 20.7457 3.32851Z" fill="#fff"/>
                                        </svg>
                                    </div>
                                    <img
                                        id="post-img"
                                        className="post-img"
                                        src=''
                                        alt="Post img"
                                    />
                                </div>

                                <div className="post-form-footer">
                                    <label htmlFor="image-input" id="file-input">
                                        <div>
                                            <svg width="22px" height="22px" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
                                                <path d="M3 11C3 7.22876 3 5.34315 4.17157 4.17157C5.34315 3 7.22876 3 11 3H13C16.7712 3 18.6569 3 19.8284 4.17157C21 5.34315 21 7.22876 21 11V13C21 16.7712 21 18.6569 19.8284 19.8284C18.6569 21 16.7712 21 13 21H11C7.22876 21 5.34315 21 4.17157 19.8284C3 18.6569 3 16.7712 3 13V11Z" stroke="#33363F" strokeWidth="2"/>
                                                <path fillRule="evenodd" clipRule="evenodd" d="M18.9997 13.5854L18.9794 13.5651C18.5898 13.1754 18.2537 12.8393 17.9536 12.5864C17.6367 12.3193 17.2917 12.0845 16.8665 11.9562C16.3014 11.7857 15.6986 11.7857 15.1335 11.9562C14.7083 12.0845 14.3633 12.3193 14.0464 12.5864C13.7463 12.8393 13.4102 13.1754 13.0206 13.5651L12.9921 13.5936C12.6852 13.9004 12.5046 14.0795 12.3645 14.1954L12.3443 14.2118L12.3317 14.1891C12.2447 14.0295 12.1435 13.7961 11.9726 13.3972L11.9191 13.2726L11.8971 13.2211L11.897 13.221C11.5411 12.3904 11.2422 11.693 10.9464 11.1673C10.6416 10.6257 10.2618 10.1178 9.66982 9.82106C9.17604 9.57352 8.6235 9.46711 8.07311 9.51356C7.41323 9.56924 6.87197 9.89977 6.38783 10.2894C5.98249 10.6157 5.52754 11.0598 5 11.5859V12.9999C5 13.5166 5.0003 13.9848 5.00308 14.411L6.117 13.2971C6.80615 12.6079 7.26639 12.1497 7.64186 11.8475C8.01276 11.5489 8.17233 11.5123 8.24128 11.5065C8.42475 11.491 8.60893 11.5265 8.77352 11.609C8.83539 11.64 8.96994 11.7333 9.20344 12.1482C9.43981 12.5682 9.69693 13.1646 10.0809 14.0605L10.1343 14.1851L10.1506 14.2232C10.2995 14.5707 10.4378 14.8936 10.5759 15.1468C10.7206 15.412 10.9308 15.7299 11.2847 15.9489C11.702 16.2072 12.1997 16.3031 12.6831 16.2182C13.093 16.1463 13.4062 15.9292 13.6391 15.7367C13.8613 15.5529 14.1096 15.3045 14.3769 15.0371L14.377 15.0371L14.4063 15.0078C14.8325 14.5816 15.1083 14.307 15.3353 14.1157C15.5526 13.9325 15.6552 13.8878 15.7112 13.8709C15.8995 13.8141 16.1005 13.8141 16.2888 13.8709C16.3448 13.8878 16.4474 13.9325 16.6647 14.1157C16.8917 14.307 17.1675 14.5816 17.5937 15.0078L18.9441 16.3582C18.9902 15.6404 18.9983 14.7479 18.9997 13.5854Z" fill="#00eeff"/>
                                                <circle cx="16.5" cy="7.5" r="1.5" fill="#00eeff"/>
                                            </svg>
                                        </div>
                                    </label>
                                    <input onChange={loadImg} id="image-input" type="file" accept=".jpg, .jpeg, .png"/>
                                    <input className="primary-btn" type="submit" value={btn_name}/>
                                </div>

                                <div id="post-header-msg-div"></div>
                            </form>
                        </div>

                    </div>
                </div>

                <div className="loading-animation"></div>

                <div className="post-animation">
                    
                    {new_posts.map(post => {
                        return <Post
                            key={post.key}
                            post={post}
                        />;
                    })}
                        
                </div>

            </div>
        </>

    );

}

export default PostForm;