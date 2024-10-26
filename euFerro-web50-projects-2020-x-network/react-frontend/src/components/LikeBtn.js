import { Link } from "react-router-dom";
import "./LikeBtn.css";
import { useEffect, useState } from "react";


export default function LikeBtn({post_id, likes}) {

    const [state, setState] = useState({
        isLiked: undefined,
        logged_user: undefined,
        likes: likes
    });

    function style_like_btn() {
        this.style.color = "#ee0055";
        this.childNodes[0].style.backgroundColor = "#330011";
        this.childNodes[0].childNodes[0].childNodes[0].style.fill = "#ee0055";
    }
    
    function unstyle_like_btn() {
        this.style.color = "#777";
        this.childNodes[0].style.backgroundColor = "transparent";
        this.childNodes[0].childNodes[0].childNodes[0].style = "";
    }
    
    function style_comment_btn() {
        this.style.color = "#00ffff";
        this.childNodes[0].style.backgroundColor = "#003333";
        this.childNodes[0].childNodes[0].childNodes[0].childNodes[0].childNodes[0].style.fill = "#00ffff";
    }
    
    function unstyle_comment_btn() {
        this.style.color = "#777";
        this.childNodes[0].style.backgroundColor = "transparent";
        this.childNodes[0].childNodes[0].childNodes[0].childNodes[0].childNodes[0].style = "";
    }

    function like() {
        const csrf_token = document.cookie.split(';')[0].split('=')[1];
        console.log(csrf_token);
        const formData = new FormData();
        formData.append("post_id", post_id)
        fetch("/like", {
            "method": "POST",
            "credentials": "same-origin",
            "headers": {
                "X-CSRFToken": csrf_token
            },
            "body": formData
        })
        .then(response => response.json())
        .then(response => {
            if (response.error) {
                alert(response.error);
                return;
            }
            if (response.ok) {
                console.log(response.ok);
                const new_logged_user = {
                    ...state.logged_user,
                    liked_posts: [...state.logged_user.liked_posts, post_id]
                };
                // console.log(new_logged_user);
                localStorage.setItem('logged_user', JSON.stringify(new_logged_user));
                let new_likes = state.likes < 0 ? 0 : state.likes + 1;
                setState({
                    isLiked: true,
                    logged_user: new_logged_user,
                    likes: new_likes
                });
            }
        })
    }

    function unlike() {
        const csrf_token = document.cookie.split(';')[0].split('=')[1];
        fetch(`/unlike/${post_id}`, {
            "method": "DELETE",
            "credentials": "same-origin",
            "headers": {
                "X-CSRFToken": csrf_token
            }
        })
        .then(response => response.json())
        .then(response => {
            if (response.error) {
                alert(`(!) Error - ${response.error}`)
            }
            if (response.ok) {
                console.log(response.ok);
                const new_liked_posts = state.logged_user.liked_posts.filter(id => {
                    return id !== post_id;
                })
                const new_logged_user = {
                    ...state.logged_user,
                    liked_posts: new_liked_posts
                };
                // console.log(new_logged_user);
                localStorage.setItem('logged_user', JSON.stringify(new_logged_user));
                let new_likes = state.likes < 0 ? 0 : state.likes - 1; 
                setState({
                    ...state,
                    likes: new_likes,
                    isLiked: false
                })
            }
        })
    }

    useEffect(() => {
        const like_divs = document.querySelectorAll('.like-div');
        like_divs.forEach(element => {
            element.onmouseover = style_like_btn;
            element.onmouseout = unstyle_like_btn;
        });

        const comment_divs = document.querySelectorAll('.comment-div');
        comment_divs.forEach(element => {
            element.onmouseover = style_comment_btn;
            element.onmouseout = unstyle_comment_btn;
        });
        if (state.logged_user === undefined) {
            const logged_user = JSON.parse(localStorage.getItem('logged_user'));
            if (logged_user !== null) {
                // console.log(logged_user);
                setState({
                    ...state,
                    logged_user: logged_user
                });
            }
        } else {
            if (state.isLiked === undefined) {
                let is_liked = false;
                for (let i = 0; i < state.logged_user.liked_posts.length; i++) {
                    if (state.logged_user.liked_posts[i] === post_id) {
                        is_liked = true;
                    }
                }
                setState({
                    ...state,
                    isLiked: is_liked
                })
            }
        }
    }, [post_id, likes, state]);

    return (
        <>
        <div className="like-div">
            <div className="footer-btn-div">

                {state.isLiked ? (
                    <svg onClick={unlike} className="footer-svg" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg">
                        <path d="M2 9.1371C2 14 6.01943 16.5914 8.96173 18.9109C10 19.7294 11 20.5 12 20.5C13 20.5 14 19.7294 15.0383 18.9109C17.9806 16.5914 22 14 22 9.1371C22 4.27416 16.4998 0.825464 12 5.50063C7.50016 0.825464 2 4.27416 2 9.1371Z" fill="rgb(238, 0, 85)"/>
                    </svg>
                ) : (
                    <>  
                    <svg onClick={like} className="footer-svg" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
                        <path className="footer-path" d="M8.96173 18.9109L9.42605 18.3219L8.96173 18.9109ZM12 5.50063L11.4596 6.02073C11.601 6.16763 11.7961 6.25063 12 6.25063C12.2039 6.25063 12.399 6.16763 12.5404 6.02073L12 5.50063ZM15.0383 18.9109L15.5026 19.4999L15.0383 18.9109ZM9.42605 18.3219C7.91039 17.1271 6.25307 15.9603 4.93829 14.4798C3.64922 13.0282 2.75 11.3345 2.75 9.1371H1.25C1.25 11.8026 2.3605 13.8361 3.81672 15.4758C5.24723 17.0866 7.07077 18.3752 8.49742 19.4999L9.42605 18.3219ZM2.75 9.1371C2.75 6.98623 3.96537 5.18252 5.62436 4.42419C7.23607 3.68748 9.40166 3.88258 11.4596 6.02073L12.5404 4.98053C10.0985 2.44352 7.26409 2.02539 5.00076 3.05996C2.78471 4.07292 1.25 6.42503 1.25 9.1371H2.75ZM8.49742 19.4999C9.00965 19.9037 9.55954 20.3343 10.1168 20.6599C10.6739 20.9854 11.3096 21.25 12 21.25V19.75C11.6904 19.75 11.3261 19.6293 10.8736 19.3648C10.4213 19.1005 9.95208 18.7366 9.42605 18.3219L8.49742 19.4999ZM15.5026 19.4999C16.9292 18.3752 18.7528 17.0866 20.1833 15.4758C21.6395 13.8361 22.75 11.8026 22.75 9.1371H21.25C21.25 11.3345 20.3508 13.0282 19.0617 14.4798C17.7469 15.9603 16.0896 17.1271 14.574 18.3219L15.5026 19.4999ZM22.75 9.1371C22.75 6.42503 21.2153 4.07292 18.9992 3.05996C16.7359 2.02539 13.9015 2.44352 11.4596 4.98053L12.5404 6.02073C14.5983 3.88258 16.7639 3.68748 18.3756 4.42419C20.0346 5.18252 21.25 6.98623 21.25 9.1371H22.75ZM14.574 18.3219C14.0479 18.7366 13.5787 19.1005 13.1264 19.3648C12.6739 19.6293 12.3096 19.75 12 19.75V21.25C12.6904 21.25 13.3261 20.9854 13.8832 20.6599C14.4405 20.3343 14.9903 19.9037 15.5026 19.4999L14.574 18.3219Z"/>
                    </svg>
                    </>
                )}
                
            </div>
            <span className="footer-num">{state.likes}</span>
        </div>
        </>
    );   
}