(function () {
  'use strict';

  var CPP98_SAMPLE = '#include <iostream>\n\nint main() {\n    int number = 4;\n    number = number + 1;\n    std::cout << number << "\\n";\n    return 0;\n}\n';
  function query(host, selector) { return host.querySelector(selector); }
  function setText(element, value) { if (element) { element.textContent = value; } }
  function announce(element, message, busy) {
    if (!element) { return; }
    element.textContent = message;
    element.setAttribute('aria-live', 'polite');
    element.setAttribute('aria-busy', busy ? 'true' : 'false');
  }
  function normalise(value) { return String(value || '').trim().replace(/\s+/g, ' ').toLowerCase(); }
  function control(host, name, alternatives) {
    return query(host, '[data-' + name + ']') || query(host, alternatives || '');
  }

  function initHighlighting() {
    var grammar = window.COS110Cpp98Grammar;
    document.querySelectorAll('[data-component="cpp-highlight"]').forEach(function (host) {
      var code = host.matches('code, pre') ? host : query(host, 'code');
      if (!code || !grammar) { return; }
      var rawCode = code.textContent;
      code.dataset.cppSource = rawCode;
      code.innerHTML = grammar.highlight(rawCode);
      code.classList.add('cpp98-code');
    });
  }

  function initMemorySteppers() {
    document.querySelectorAll('[data-component="memory-stepper"]').forEach(function (host) {
      var steps = Array.prototype.slice.call(host.querySelectorAll('[data-memory-step], .memory-step'));
      if (!steps.length) { return; }
      var previous = control(host, 'memory-prev', '[data-step-prev]');
      var next = control(host, 'memory-next', '[data-step-next]');
      var status = control(host, 'memory-status', '[data-step-status]');
      var activeIndex = 0;
      host.setAttribute('role', 'group');
      host.setAttribute('aria-roledescription', 'memory sequence');
      function render(index, focusStep) {
        activeIndex = Math.max(0, Math.min(index, steps.length - 1));
        steps.forEach(function (step, stepIndex) {
          var active = stepIndex === activeIndex;
          step.hidden = !active;
          step.tabIndex = active ? 0 : -1;
          step.setAttribute('aria-current', active ? 'step' : 'false');
        });
        if (previous) { previous.disabled = activeIndex === 0; }
        if (next) { next.disabled = activeIndex === steps.length - 1; }
        announce(status, 'Step ' + (activeIndex + 1) + ' of ' + steps.length + '.', false);
        if (focusStep) { steps[activeIndex].focus(); }
      }
      if (previous) { previous.addEventListener('click', function () { render(activeIndex - 1, true); }); }
      if (next) { next.addEventListener('click', function () { render(activeIndex + 1, true); }); }
      host.addEventListener('keydown', function (event) {
        if (event.key === 'ArrowLeft') { event.preventDefault(); render(activeIndex - 1, true); }
        if (event.key === 'ArrowRight') { event.preventDefault(); render(activeIndex + 1, true); }
        if (event.key === 'Home') { event.preventDefault(); render(0, true); }
        if (event.key === 'End') { event.preventDefault(); render(steps.length - 1, true); }
      });
      render(0, false);
    });
  }

  function initRunners() {
    document.querySelectorAll('[data-component="cpp-runner"]').forEach(function (host) {
      var code = control(host, 'runner-code', 'textarea, [contenteditable="true"]');
      var run = control(host, 'runner-run', 'button[type="submit"]');
      var reset = control(host, 'runner-reset');
      var copy = control(host, 'runner-copy');
      var output = control(host, 'runner-output', 'output, pre');
      var prediction = control(host, 'runner-prediction');
      var fallback = control(host, 'runner-fallback');
      var highlightedCode = query(host, '[data-runner-highlight] code');
      var grammar = window.COS110Cpp98Grammar;
      if (!code) { return; }
      var originalCode = code.value !== undefined ? code.value : code.textContent;
      originalCode = originalCode.trim() || CPP98_SAMPLE;
      function readCode() { return code.value !== undefined ? code.value : code.textContent; }
      function updateHighlight(value) {
        if (!highlightedCode) { return; }
        highlightedCode.innerHTML = grammar ? grammar.highlight(value) : value.replace(/&/g, '&amp;').replace(/</g, '&lt;');
      }
      function writeCode(value) { if (code.value !== undefined) { code.value = value; } else { code.textContent = value; } updateHighlight(value); }
      function fallbackMessage() {
        return 'If no result appears, keep changing the numbers and trace the statements one at a time.';
      }
      function reportFallback(message) { announce(fallback, message || fallbackMessage(), false); }
      writeCode(originalCode);
      reportFallback();
      code.addEventListener('input', function () { updateHighlight(readCode()); });
      code.addEventListener('scroll', function () {
        var highlightedLayer = query(host, '[data-runner-highlight]');
        if (highlightedLayer) { highlightedLayer.scrollTop = code.scrollTop; highlightedLayer.scrollLeft = code.scrollLeft; }
      });
      if (run) {
        run.addEventListener('click', function (event) {
          event.preventDefault();
          var source = readCode();
          if (!source.trim()) { announce(output, 'Add code before running it.', false); reportFallback(); return; }
          run.disabled = true;
          announce(output, 'Getting a result…', true);
          reportFallback('Running your changed code…');
          fetch('https://wandbox.org/api/compile.json', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({
              compiler: 'gcc-12.3.0',
              code: source,
              'compiler-option-raw': '-std=c++98\n-Wall\n-Wextra\n-pedantic'
            })
          }).then(function (response) {
            if (!response.ok) { throw new Error('No result was received.'); }
            return response.json();
          }).then(function (result) {
            var compilerText = (result.compiler_error || result.compiler_output || '').trim();
            var programText = (result.program_output || result.program_error || result.status || '').trim();
            if (result.status === '0' || result.status === 0) {
              announce(output, programText || '(The program produced no output.)', false);
              reportFallback('Result received. Change one number and run it again.');
            } else {
              announce(output, compilerText || programText || 'The code needs a fix before it can run.', false);
              reportFallback('Check one change at a time. ' + fallbackMessage());
            }
          }).catch(function () {
            announce(output, 'No result was received right now.', false);
            reportFallback();
          }).finally(function () { run.disabled = false; });
        });
      }
      if (reset) {
        reset.addEventListener('click', function (event) {
          event.preventDefault(); writeCode(originalCode);
          if (prediction) { prediction.value = ''; }
          announce(output, 'Ready. Change a number, then run the code.', false); reportFallback();
        });
      }
      if (copy) {
        copy.addEventListener('click', function (event) {
          event.preventDefault();
          var source = readCode();
          var copied = navigator.clipboard && navigator.clipboard.writeText ? navigator.clipboard.writeText(source) : Promise.reject();
          copied.then(function () { announce(output, 'Code copied.', false); }).catch(function () {
            if (code.select) { code.select(); document.execCommand('copy'); announce(output, 'Code copied.', false); }
            else { announce(output, 'Copy is unavailable. Select the code and copy it manually.', false); }
          });
        });
      }
    });
  }

  function initPracticeReveals() {
    document.querySelectorAll('[data-component="practice-reveal"]').forEach(function (host) {
      var toggle = control(host, 'practice-toggle', 'button');
      var solution = control(host, 'practice-solution', '.practice-solution');
      if (!toggle || !solution) { return; }
      var solutionId = solution.id || 'practice-solution-' + Math.random().toString(36).slice(2);
      solution.id = solutionId;
      toggle.setAttribute('aria-controls', solutionId);
      function render(revealed) { solution.hidden = !revealed; toggle.setAttribute('aria-expanded', String(revealed)); }
      toggle.addEventListener('click', function () { render(solution.hidden); });
      render(false);
    });
  }

  function initQuizzes() {
    document.querySelectorAll('[data-component="quiz-check"]').forEach(function (card) {
      var answer = control(card, 'quiz-answer', 'input, textarea, select');
      var submit = control(card, 'quiz-submit', 'button[type="submit"]');
      var feedback = control(card, 'quiz-feedback', '[role="status"], .quiz-feedback');
      var key = card.dataset.answer || card.dataset.correctAnswer || '';
      if (!answer || !feedback || !key) { return; }
      function show(state) {
        var message = card.dataset['feedback' + state] || '';
        feedback.dataset.state = state.toLowerCase();
        announce(feedback, message, false);
        answer.setAttribute('aria-invalid', state === 'Incorrect' ? 'true' : 'false');
      }
      function check(event) {
        if (event) { event.preventDefault(); }
        var given = normalise(answer.value);
        if (!given) { show('Blank'); return; }
        var acceptable = key.split('|').map(normalise);
        show(acceptable.indexOf(given) !== -1 ? 'Correct' : 'Incorrect');
      }
      if (submit) { submit.addEventListener('click', check); }
      var form = card.closest('form');
      if (form) { form.addEventListener('submit', check); }
    });
  }

  function init() { initHighlighting(); initMemorySteppers(); initRunners(); initPracticeReveals(); initQuizzes(); }
  if (document.readyState === 'loading') { document.addEventListener('DOMContentLoaded', init); } else { init(); }
}());
