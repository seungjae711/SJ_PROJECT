

firebase.auth().onAuthStateChanged(function(user) {
    if (user) {
  
      document.getElementById("list_div").style.display = "block";
      document.getElementById("login_div").style.display = "none";
  
      var user = firebase.auth().currentUser;
  
      if(user != null){
  
        var email_id = user.email;
        document.getElementById("user_para").innerHTML = "Welcome to our issue tracker! " + email_id + "!!";
        
      }
  
    } else {
    
      document.getElementById("list_div").style.display = "none";
      document.getElementById("login_div").style.display = "block";
  
    }
  });
  
  function login(){
  
    var userEmail = document.getElementById("txtEmail").value;
    var userPass = document.getElementById("txtPassword").value;
  
    firebase.auth().signInWithEmailAndPassword(userEmail, userPass).catch(function(error) {
      var errorCode = error.code;
      var errorMessage = error.message;
  
      window.alert(errorMessage);
  
    });
  
  }

  function createID() {
    var userEmail = document.getElementById("txtEmail").value;
    var userPass = document.getElementById("txtPassword").value;

    firebase.auth().createUserWithEmailAndPassword(userEmail, userPass).catch(function(error) {
        // Handle Errors here.
        var errorCode = error.code;
        var errorMessage = error.message;
    
        window.alert("Error : " + errorMessage);
    
    });    
  }
  
  function logout(){
    firebase.auth().signOut();
  }
  
