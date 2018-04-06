

<!DOCTYPE html>
<html>
<head>
  <script type="text/javascript" src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
  <link rel = "stylesheet" type = "text/css" href = "css/main.css" />
  <script>

      $(document).ready(function() {
          $('#buttonid').on('click', function(e) {
              e.preventDefault(); // prevent page from reloading.
              $.ajax({
                type: "POST",
                url: "callProg.php",
                data: { cipher_text: $("#input-box").val()},
                dataType: 'json',
                success: function(data) {
                  var result = data[0].split("#");
                  $("#output-box").html(result[1] + '\n' + result[2] + '\n' + result[3]);
                }
              });
          });
      });

  </script>
</head>
<body>
<div id="content">
  <div id="title">
    <h2>VigenereVictory</h2>
    <p><a href="https://github.com/ajze/vigenere-victory">github.com/ajze/vigenere-victory</a></p>
  </div>
  <div id="input">
    <textarea id="input-box" rows="10" cols="120"></textarea>
  </div>
  <input type="submit" id="buttonid" value="DECRYPT"/>
  <div id="output">
    <textarea id="output-box" rows="10" cols="120"></textarea>
  </div>
</div>
</body>
</html>
