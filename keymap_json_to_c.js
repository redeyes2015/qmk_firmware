#!/usr/bin/env node

const jsonFile = process.argv[2];


const fs = require('fs');

const jsonText = fs.readFileSync(jsonFile);

const layers = JSON.parse(jsonText).layers;


for (const [index, layer]  of layers.entries()) {
    console.log(`\t[${index}] = LAYOUT(${layer.join(', ')})${(index + 1 == layers.length) ? '' : ','}`);
}

