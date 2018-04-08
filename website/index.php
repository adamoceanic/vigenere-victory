<!DOCTYPE html>
<html>
<head>
  <script type="text/javascript" src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
  <link rel = "stylesheet" type = "text/css" href = "css/main.css" />
  <script>
      $(document).ready(function() {
          $('#button').on('click', function(e) {
              e.preventDefault(); // prevent page from reloading.
              var ct = $("#input-box").val();
              if (ct.length < 800) {
                $("#error-msg").removeClass("hide_error").addClass("show_error");
              }
              else {
                $.ajax({
                  type: "POST",
                  url: "callProg.php",
                  data: { cipher_text: ct},
                  dataType: 'json',
                  success: function(data) {
                    var result = data[0].split("#");
                    $("#output-box").html(result[1] + '\n' + result[2] + '\n' + result[3]);
                  }
                });
              }
          });

          $('#input-box').on('click', function(e) {
            $(this).html("");
            $(this).removeClass("grey-text").addClass("black_text");
            $("#error-msg").removeClass("show_error").addClass("hide_error");
          });
      });

  </script>
</head>
<body>
<div id="content">
  <div id="title">
    <h2>VigenereVictory</h2>
    <p><a href="https://github.com/ajze/vigenere-victory">github.com/ajze/vigenere-victory</a></p>
    <p>This was put together quickly as a demonstration and potentially buggy. Any problems will be fixed soon.</p>
    <div id="error-msg" class="hide_error"><p>Error: This application has not yet been proven to work consistently for strings
    less than length 800 chars.</p></div>
  </div>
  <div id="input">
    <textarea id="input-box" class="grey-text" rows="10" cols="120">
      PASTE IN YOUR ALL CAPS CIPHERTEXT HERE
    </textarea>
  </div>
  <input type="submit" id="button" value="DECRYPT"/>
  <div id="output">
    <textarea readonly id="output-box" rows="10" cols="120"></textarea>
  </div>
</div>
</body>
</html>
