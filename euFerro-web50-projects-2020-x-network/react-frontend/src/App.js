// Import Pages
import './App.css';

// Import Components
import './components/MainLink'
import Homepage from './pages/Homepage';
import Loginpage from './pages/Loginpage';
import Registerpage from './pages/Registerpage';
import Sidebar from './components/Sidebar';
import { Routes, Route } from 'react-router-dom';
import { useEffect, useState } from 'react';
import Profilepage from './pages/Profilepage';
import PostPage from './pages/PostPage';
import Likedpage from './pages/Likedpage';
import EditPost from './pages/EditPost';


function App() {

  const [user, setUser] = useState(undefined)

  function resizeMain() {
    console.log('RESIZE MAIN');
    const sidebar = document.querySelector('#side-bar');
    const main = document.querySelector('main');
    
    if (window.innerWidth >= 660) {
      main.style.width = window.innerWidth - sidebar.offsetWidth + 'px';
      main.style.left = sidebar.offsetWidth + 'px';
    } else {
      main.style.left = '0px';
      main.style.width = '100vw';
    }
    
  }

  function get_logged_user() {
    
    const logged_user = JSON.parse(localStorage.getItem("logged_user"));
    fetch("/profile", {
      "method": "GET"
    })
    .then(response => response.json())
    .then(response => {
      if (logged_user !== response.user) {
        console.log('User changed');
        setUser(response.user);
        localStorage.setItem("logged_user", response.user);
      }
    })

  }

  useEffect(() => {
    const urlParams = new URLSearchParams(window.location.search);
    const redirect_url = urlParams.get("redirect_url");
    console.log(`Redirect Url = ${redirect_url}`);
    if (window.location.pathname === '/') {
      window.location.replace('/home');
    } else {
      if (redirect_url !== null) {
        window.location.replace(redirect_url);
      }
    }

    resizeMain();
    window.addEventListener('resize', resizeMain);

    get_logged_user();
  });

  return (
      <div className="App">

      <nav>
          <Sidebar user={user}/>
      </nav>
          
      <main>
          <div className="main">
            <Routes>
              <Route path='/home' element={<Homepage/>}/>
              <Route path='/search'/>
              <Route path='/profile/:username' element={<Profilepage/>}/>
              <Route path='/post/:id' element={<PostPage/>}/>
              <Route path='/login' element={<Loginpage/>}/>
              <Route path='/register' element={<Registerpage/>}/>
              <Route path='/liked/:username' element={<Likedpage/>}/>
              <Route path='/edit/:post_id' element={<EditPost/>}/>
              <Route path='*' element={<div className='nothing-here'>Not Found 404</div>}/>
            </Routes>
          </div>
      </main>

      </div>
  );
}

export default App;
