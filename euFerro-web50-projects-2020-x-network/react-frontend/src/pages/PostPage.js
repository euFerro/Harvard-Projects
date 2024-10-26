import { useParams } from "react-router-dom";
import Post from "../components/Post";
import { useEffect, useState } from "react";
import BackBar from "../components/BackBar";
import PostForm from "../components/PostForm";


function PostPage() {
    const {id} = useParams();
    const [post, setPost] = useState([]);
    const [comments, setComments] = useState([]);

    const logged_user = JSON.parse(localStorage.getItem('logged_user'));
    if  (logged_user !== undefined) {
        console.log(logged_user);
    }

    function getPost() {
        fetch(`/posts?q=single-post&post_id=${id}`, {
            "method": "GET",
        })
        .then(response => response.json())
        .then(response => {
            if (response.error) {
                alert(response.error)
            } else {
                const posts = JSON.parse(response);
                console.log(response);
                console.log(posts);
                setPost(post.concat(posts))
                console.log('Post was successfully fetched!');
            }
        })
    }

    useEffect(() => {
        console.log(`POST.LENGTH : ${post.length}`);
        console.log(`POST_ID : ${id}`);
        if (post.length === 0) {
            getPost();  
        }
        if (comments.length === 0) {
            // Get comments
        }
    }, [post, comments])

    return (
        <>

        <BackBar title={'Post'}/>

        {post.length !== 0 ? (
            <>
            {post.map(post => {
                return <Post post={post}/>;
            })}
            </>
        ) : (
            <><div>(!) Error: You are probably offline try again</div></>
        )}

        <div id="all-posts-div">

        {logged_user && post.length !== 0 ? (
            <>
            <PostForm
                user={logged_user}
                title={'New Comment'}
                placeholder={`Post your response to @${post[0].username}`}
                btn_name={'Comment'}/>
            </>
        ) : (
            <></>
        )}

        {comments.length !== 0 ? (
            <>
            {comments.map(post => {
                return <Post
                    key={post.key}
                    post={post}
                />;
            })}
            </>
        ) : (
            <><div className="nothing-here">No comments yet.</div></>
        )}

        </div>

        </>
    
    );
}

export default PostPage;