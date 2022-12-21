const Row = require('../Row.js');

const test = require('tap').test;
const lpsolve = require('../index.js');


test('constructor', (t) => {
    t.plan(2)
    const r = new Row();
    r.Add('a', 1)
    const r2 = new lpsolve.Row(r);
    t.same(r2.raw, r.raw, 'clone');
    const r3 = new lpsolve.Row(r.raw);
    t.same(r3.raw, r.raw, 'clone');
})

test('add', (t) => {
    t.plan(3);
    const r = new Row();
    r.Add('a', 1)
    t.same(r.raw, { 'a': 1 })
    r.Add({ 'a': 1 })
    t.same(r.raw, { 'a': 2 })
    const r_part = new lpsolve.Row().Add('a', 1).Add('b', 1);
    r.Add(r_part);
    t.same(r.raw, { 'a': 3, 'b': 1 })
});

test('subtract', (t) => {
    t.plan(3);
    const r = new Row();
    r.Subtract('a', 1)
    t.same(r.raw, { 'a': -1 })
    r.Subtract({ 'a': 1 })
    t.same(r.raw, { 'a': -2 })
    const r_part = new lpsolve.Row().Add('a', 1).Add('b', 1);
    r.Subtract(r_part);
    t.same(r.raw, { 'a': -3 , 'b': -1})
});

test('multiply', (t) => {
    t.plan(2);
    const r = new Row();
    r.Add('a', 1)
    r.Multiply(2)
    t.same(r.raw, { 'a': 2 })
    r.Multiply(0)
    t.same(r.raw, {})
});

test('totext', (t) => {
    t.plan(2);
    t.same(new Row({ a: 1, b: 2, c: -1, d: 0, constant: 1 }).ToText(), " +1 a +2 b -1 c +1")
    t.same(new Row().ToText(), "0")
});