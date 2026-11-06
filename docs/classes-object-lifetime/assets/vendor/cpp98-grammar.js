(function (root) {
  'use strict';

  var KEYWORDS = new Set([
    'asm', 'auto', 'bool', 'break', 'case', 'catch', 'char', 'class', 'const',
    'const_cast', 'continue', 'default', 'delete', 'do', 'double', 'dynamic_cast',
    'else', 'enum', 'explicit', 'export', 'extern', 'false', 'float', 'for',
    'friend', 'goto', 'if', 'inline', 'int', 'long', 'mutable', 'namespace',
    'new', 'operator', 'private', 'protected', 'public', 'register',
    'reinterpret_cast', 'return', 'short', 'signed', 'sizeof', 'static',
    'static_cast', 'struct', 'switch', 'template', 'this', 'throw', 'true',
    'try', 'typedef', 'typeid', 'typename', 'union', 'unsigned', 'using',
    'virtual', 'void', 'volatile', 'wchar_t', 'while'
  ]);
  var TYPES = new Set(['size_t', 'ptrdiff_t', 'NULL', 'std', 'string', 'istream', 'ostream', 'iostream']);
  var OPERATORS = [
    '>>=', '<<=', '->*', '...', '++', '--', '->', '<<', '>>', '<=', '>=', '==', '!=',
    '&&', '||', '+=', '-=', '*=', '/=', '%=', '&=', '|=', '^=', '::', '.*',
    '+', '-', '*', '/', '%', '=', '<', '>', '!', '~', '&', '|', '^', '?', ':', ';', ',', '.', '(', ')', '[', ']', '{', '}'
  ];

  function isIdentifierStart(character) { return /[A-Za-z_]/.test(character); }
  function isIdentifierPart(character) { return /[A-Za-z0-9_]/.test(character); }
  function isDigit(character) { return /[0-9]/.test(character); }
  function escapeHtml(text) {
    return text.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
  }
  function token(kind, value) {
    return '<span class="tok-' + kind + '">' + escapeHtml(value) + '</span>';
  }
  function nextNonSpace(source, index) {
    while (index < source.length && /\s/.test(source.charAt(index))) { index += 1; }
    return source.charAt(index);
  }
  function readQuoted(source, index, quote) {
    var cursor = index + 1;
    while (cursor < source.length) {
      if (source.charAt(cursor) === '\\') { cursor += 2; continue; }
      if (source.charAt(cursor) === quote) { return cursor + 1; }
      cursor += 1;
    }
    return source.length;
  }
  function readNumber(source, index) {
    var remaining = source.slice(index);
    var match = remaining.match(/^(?:0[xX][0-9A-Fa-f]+|0[0-7]*|(?:\d+\.\d*|\.\d+|\d+)(?:[eE][+-]?\d+)?)[uUlLfF]*/);
    return match ? index + match[0].length : index + 1;
  }
  function findOperator(source, index) {
    for (var operatorIndex = 0; operatorIndex < OPERATORS.length; operatorIndex += 1) {
      if (source.slice(index, index + OPERATORS[operatorIndex].length) === OPERATORS[operatorIndex]) {
        return OPERATORS[operatorIndex];
      }
    }
    return null;
  }

  function highlight(source) {
    var output = '';
    var index = 0;
    var atLineStart = true;
    while (index < source.length) {
      var current = source.charAt(index);
      if (current === '\n') { output += '\n'; index += 1; atLineStart = true; continue; }
      if (/\s/.test(current)) { output += escapeHtml(current); index += 1; continue; }
      if (atLineStart && current === '#') {
        var directiveEnd = source.indexOf('\n', index);
        if (directiveEnd === -1) { directiveEnd = source.length; }
        output += token('preprocessor', source.slice(index, directiveEnd));
        index = directiveEnd;
        atLineStart = false;
        continue;
      }
      atLineStart = false;
      if (source.slice(index, index + 2) === '//') {
        var lineEnd = source.indexOf('\n', index);
        if (lineEnd === -1) { lineEnd = source.length; }
        output += token('comment', source.slice(index, lineEnd)); index = lineEnd; continue;
      }
      if (source.slice(index, index + 2) === '/*') {
        var commentEnd = source.indexOf('*/', index + 2);
        commentEnd = commentEnd === -1 ? source.length : commentEnd + 2;
        output += token('comment', source.slice(index, commentEnd)); index = commentEnd; continue;
      }
      if (current === '"' || current === "'") {
        var quoteEnd = readQuoted(source, index, current);
        output += token(current === '"' ? 'string' : 'character', source.slice(index, quoteEnd)); index = quoteEnd; continue;
      }
      if (isDigit(current) || (current === '.' && isDigit(source.charAt(index + 1)))) {
        var numberEnd = readNumber(source, index);
        output += token('number', source.slice(index, numberEnd)); index = numberEnd; continue;
      }
      if (isIdentifierStart(current)) {
        var identifierEnd = index + 1;
        while (isIdentifierPart(source.charAt(identifierEnd))) { identifierEnd += 1; }
        var identifier = source.slice(index, identifierEnd);
        if (KEYWORDS.has(identifier)) { output += token('keyword', identifier); }
        else if (TYPES.has(identifier)) { output += token('type', identifier); }
        else if (nextNonSpace(source, identifierEnd) === '(') { output += token('function', identifier); }
        else { output += escapeHtml(identifier); }
        index = identifierEnd; continue;
      }
      var operatorValue = findOperator(source, index);
      if (operatorValue) { output += token('operator', operatorValue); index += operatorValue.length; continue; }
      output += escapeHtml(current); index += 1;
    }
    return output;
  }

  root.COS110Cpp98Grammar = { highlight: highlight };
}(window));
