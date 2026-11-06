(function () {
  "use strict";
  function escapeHtml(text) {
    return text.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;");
  }
  function colourCpp(code) {
    var text = code.textContent;
    var pattern = /(\/\/[^\n]*|#[^\n]*|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|\b(?:class|public|protected|private|const|void|int|char|bool|return|if|else|new|delete|this|static|friend|include|using|namespace|std)\b)/g;
    var out = "", last = 0, match;
    while ((match = pattern.exec(text)) !== null) {
      out += escapeHtml(text.slice(last, match.index));
      var token = match[0], kind = "tok-key";
      if (token.slice(0, 2) === "//") kind = "tok-com";
      else if (token.charAt(0) === "#") kind = "tok-pre";
      else if (token.charAt(0) === '"' || token.charAt(0) === "'") kind = "tok-str";
      out += '<span class="' + kind + '">' + escapeHtml(token) + "</span>";
      last = pattern.lastIndex;
    }
    out += escapeHtml(text.slice(last));
    code.innerHTML = out;
  }
  function addCopyButton(pre) {
    var wrap = document.createElement("div");
    wrap.className = "code-wrap";
    pre.parentNode.insertBefore(wrap, pre);
    wrap.appendChild(pre);
    var button = document.createElement("button");
    button.className = "copy";
    button.type = "button";
    button.textContent = "Copy";
    button.addEventListener("click", function () {
      var text = pre.textContent;
      function feedback(ok) {
        button.textContent = ok ? "Copied" : "Select and copy";
        window.setTimeout(function () { button.textContent = "Copy"; }, 1500);
      }
      function fallback() {
        var area = document.createElement("textarea");
        area.value = text;
        area.setAttribute("readonly", "");
        area.style.position = "fixed";
        area.style.left = "-9999px";
        document.body.appendChild(area);
        area.select();
        var ok = false;
        try { ok = document.execCommand("copy"); } catch (error) { ok = false; }
        document.body.removeChild(area);
        feedback(ok);
      }
      if (navigator.clipboard && typeof navigator.clipboard.writeText === "function") {
        navigator.clipboard.writeText(text).then(function () { feedback(true); }, fallback);
      } else {
        fallback();
      }
    });
    wrap.appendChild(button);
  }
  function setAll(open) {
    document.querySelectorAll("details.solution").forEach(function (item) { item.open = open; });
  }
  function openSolution(hash) {
    if (!hash || hash.charAt(0) !== "#") return;
    var target = document.getElementById(hash.slice(1));
    if (target && target.tagName.toLowerCase() === "details") target.open = true;
  }
  document.addEventListener("DOMContentLoaded", function () {
    document.querySelectorAll("pre code.language-cpp").forEach(colourCpp);
    document.querySelectorAll("pre").forEach(addCopyButton);
    var expand = document.querySelector("[data-expand]");
    var collapse = document.querySelector("[data-collapse]");
    if (expand) expand.addEventListener("click", function () { setAll(true); });
    if (collapse) collapse.addEventListener("click", function () { setAll(false); });
    document.querySelectorAll('a[href^="#"]').forEach(function (link) {
      link.addEventListener("click", function () { openSolution(link.getAttribute("href")); });
    });
    window.addEventListener("hashchange", function () { openSolution(window.location.hash); });
    openSolution(window.location.hash);
  });
}());
