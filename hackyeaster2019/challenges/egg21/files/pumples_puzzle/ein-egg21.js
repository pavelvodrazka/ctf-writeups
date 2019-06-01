'use strict';

const EinLib = require('./ein-lib');

let data = {
	positions: 5,
	names: ['Thumper', 'Angel', 'Midnight', 'Bunny', 'Snowball'],
	colors: ['Yellow', 'White', 'Green', 'Blue', 'Red'],
	characteristics: ['Scared', 'Lovely', 'Funny', 'Handsome', 'Attractive'],
	starsigns: ['Taurus', 'Virgo', 'Pisces', 'Aquarius', 'Capricorn'],
	masks: ['Chequered', 'One-coloured', 'Camouflaged', 'Dotted', 'Striped'],
};

let ein = new EinLib.einConstructor();
ein.analyze(data);

// The backpack of Thumper is yellow.
ein.same('Thumper', 'Yellow');
// Angel's star sign is taurus.
ein.same('Angel', 'Taurus');
// The one-coloured backpack is also white.
ein.same('One-coloured', 'White');
// The chequered backpack by Bunny was expensive.
ein.same('Bunny', 'Chequered');
// The bunny with the white backpack sits next to the bunny with the green backpack, on the left.
ein.neighbours('White', 'Green', true);
// The virgo is also scared.
ein.same('Virgo', 'Scared');
// The lovely bunny has a blue backpack.
ein.same('Lovely', 'Blue');
// The bunny with the camouflaged backpack sits in the middle.
ein.same(3, 'Camouflaged');
// Snowball is the first bunny.
ein.same(1, 'Snowball');
// The bunny with a striped backpack sits next to the funny bunny.
ein.neighbours('Striped', 'Funny');
// The funny bunny sits also next to the pisces.
ein.neighbours('Funny', 'Pisces');
// The lovely bunny sits next to the aquarius.
ein.neighbours('Lovely', 'Aquarius');
// The backpack of the handsome bunny is dotted.
ein.same('Handsome', 'Dotted');
// Midnight is a attractive bunny.
ein.same('Midnight', 'Attractive');
// Snowball sits next to the bunny with a red backpack.
ein.neighbours('Snowball', 'Red');

console.time("Time");
ein.solve();
console.timeEnd("Time");

process.exit(0);
