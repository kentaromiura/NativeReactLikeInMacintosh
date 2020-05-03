const fs = require('fs');

const babel = require('@babel/core'),
  presetEnv = require('@babel/preset-env'),
  presetReact = require('@babel/preset-react'),
  transformClasses = require('@babel/plugin-transform-classes');

const input = fs.readFileSync('./app/index.js', 'utf8');
const fakeReact = fs.readFileSync('./app/fakeReact.js', 'utf8');

const asResource = (input, id = 128) => {
    const toHex = input => {
        const result = [];
        let next = input;
        while(next.length) {
            const next16 = next
                .slice(0,16)
                .padEnd(16, '\0')
                .split('')
                .map(x => x.charCodeAt(0).toString(16).padStart(2, '0'));
            result.push(` $"${next16[0]}${next16[1]} ${next16[2]}${next16[3]} ${next16[4]}${next16[5]} ${next16[6]}${next16[7]} ${next16[8]}${next16[9]} ${next16[10]}${next16[11]} ${next16[12]}${next16[13]} ${next16[14]}${next16[15]}"`)
            next = next.slice(16);
        }
        return result.join('\n');
    }
return `data 'TEXT' (${id}) {
${toHex(input)}
};`
}

const main = asResource(babel.transform(input, {
    filename: 'index.js',
    presets: [[presetEnv, {
        "targets": {
          "browsers": ["ie < 8"]
        }
      }],presetReact],
    plugins: [transformClasses],
    retainLines: true
}).code.replace('"use strict";', ''));

const react = asResource(babel.transform(fakeReact, {
    filename: 'react.js',
    presets: [[presetEnv, {
        "targets": {
          "browsers": ["ie < 8"]
        }
      }],presetReact],
    plugins: [transformClasses],
    retainLines: true
}).code.replace('"use strict";', ''), 129);

const template = fs.readFileSync('./dialog.tpl');

console.log(`${template}

${main}

${react}`);
