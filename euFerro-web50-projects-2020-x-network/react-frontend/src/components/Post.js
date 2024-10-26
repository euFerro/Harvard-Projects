import { Link } from "react-router-dom";
import "./Post.css"
import LikeBtn from "./LikeBtn";

// key={post.key}
// user_id={post.user_id}
// post.profile_picture_url={post.post.profile_picture_url}
// post.username={post.post.username}
// text={post.text}
// post.created_at={post.created_at}
// post_img_url={post.image_url}
// likes={post.likes}
// comment_count={post.comment_count}

function Post({post}) {    

    console.log(post);
    let post_img = '';
    if (post.image_url !== '') {

        post_img = <div className="post-img-div">
                        <img
                            className="post-img"
                            src={post.image_url}
                            alt="Post img"
                        />
                    </div>
    }

    const logged_user = JSON.parse(localStorage.getItem("logged_user"));

    return(

        <>
            <div className="post">

                <div className="post-profile-div">
                    <Link to={'/profile/' + post.username}>
                        <img
                            className="profile-pic"
                            alt="Avatar"
                            src={post.profile_picture_url}
                        />
                    </Link>
                </div>

                <div className="post-content">

                    <div className="post-header">
                        <Link className="name-link" to={'/profile/' + post.username}>
                            <span className="post-fullname">
                                {post.username}
                            </span>
                        </Link>
                        <span className="post-info">
                            @{post.username}
                        </span>
                        <span className="post-info">
                            {post.created_at.hour}:{post.created_at.minute} {post.created_at.month}/{post.created_at.day}/{post.created_at.year}
                        </span>
                    </div>
                    <Link className='nodecoration' to={`/post/${post.key}`}>
                        <div className="post-text">{post.text}</div>
                        {post_img}
                    </Link>

                    <div className="post-footer">

                        <LikeBtn post_id={post.key} likes={post.likes}/>

                        <div className="comment-div">
                            <div className="footer-btn-div">
                                <svg className="footer-svg" viewBox="0 0 32 32" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlnsXlink="http://www.w3.org/1999/xlink" xmlnssketch="http://www.bohemiancoding.com/sketch/ns">
                                    <g stroke="none" strokeWidth="1" fill="none" fillRule="evenodd" sketchtype="MSPage">
                                        <g sketchtype="MSLayerGroup" transform="translate(-100.000000, -255.000000)" fill="#000000">
                                            <path className="footer-path" fill="#777" d="M116,281 C114.832,281 113.704,280.864 112.62,280.633 L107.912,283.463 L107.975,278.824 C104.366,276.654 102,273.066 102,269 C102,262.373 108.268,257 116,257 C123.732,257 130,262.373 130,269 C130,275.628 123.732,281 116,281 L116,281 Z M116,255 C107.164,255 100,261.269 100,269 C100,273.419 102.345,277.354 106,279.919 L106,287 L113.009,282.747 C113.979,282.907 114.977,283 116,283 C124.836,283 132,276.732 132,269 C132,261.269 124.836,255 116,255 L116,255 Z" sketchtype="MSShapeGroup"></path>
                                        </g>
                                    </g>
                                </svg>
                            </div>
                            <span className="footer-num">{post.comment_count}</span>
                        </div>
                        
                        {logged_user !== null ? (
                            <>
                            {logged_user.username === post.username ? (

                                <Link to={`/edit/${post.key}`} state={{post: post}}>
                                    <div className="comment-div">
                                        <div className="footer-btn-div">
                                            <svg className="footer-svg" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
                                                <path d="M21.2799 6.40005L11.7399 15.94C10.7899 16.89 7.96987 17.33 7.33987 16.7C6.70987 16.07 7.13987 13.25 8.08987 12.3L17.6399 2.75002C17.8754 2.49308 18.1605 2.28654 18.4781 2.14284C18.7956 1.99914 19.139 1.92124 19.4875 1.9139C19.8359 1.90657 20.1823 1.96991 20.5056 2.10012C20.8289 2.23033 21.1225 2.42473 21.3686 2.67153C21.6147 2.91833 21.8083 3.21243 21.9376 3.53609C22.0669 3.85976 22.1294 4.20626 22.1211 4.55471C22.1128 4.90316 22.0339 5.24635 21.8894 5.5635C21.7448 5.88065 21.5375 6.16524 21.2799 6.40005V6.40005Z" stroke="#777" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"/>
                                                <path d="M11 4H6C4.93913 4 3.92178 4.42142 3.17163 5.17157C2.42149 5.92172 2 6.93913 2 8V18C2 19.0609 2.42149 20.0783 3.17163 20.8284C3.92178 21.5786 4.93913 22 6 22H17C19.21 22 20 20.2 20 18V13" stroke="#777" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"/>
                                            </svg>
                                        </div>
                                    </div>
                                </Link>

                            ) : (
                                <></>
                            )}
                            </>
                        ) : (
                            <></>
                        )}

                    </div>

                </div>

            </div>
        </>

    );

}

export default Post;
