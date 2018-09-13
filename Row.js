// class to hold factor:attribute pairs
class Row {
  constructor(clone) {
    this.raw = {};

    if (clone) {
      if (clone.raw) clone = clone.raw;
      for (const k in clone) { this.raw[k] = clone[k]; }
    }
  }

  // adds a row or a variable:factor to this row
  Add(b, c) {
    const a = this.raw;
    if (c === undefined) {
      if (b.raw !== undefined) b = b.raw;
      for (const k in b) {
        a[k] = (a[k] || 0) + b[k];
      }
    } else {
      a[b] = (a[b] || 0) + c;
    }
    return this;
  }

  // subtract a row or variable:factor to this row
  Subtract(b, c) {
    const a = this.raw;
    if (c === undefined) {
      if (b.raw !== undefined) b = b.raw;
      for (const k in b) {
        a[k] = (a[k] || 0) - b[k];
      }
    } else {
      a[b] = (a[b] || 0) - c;
    }
    return this;
  }

  // multiplies all the factors by a fixed value
  Multiply(v) {
    const a = this.raw;
    if (v === 0) {
      this.raw = {};
    } else {
      for (const k in a) {
        a[k] = a[k] * v;
      }
    }

    return this;
  }

  // converts an object of vairable:factor to an equation for LP Solve
  ToText() {
    const a = this.raw;
    let ret = '';
    for (const k in a) {
      let v = a[k];
      if (v === 0) { continue; }
      if (v < 0) {
        ret += ' -';
        v = -v;
      } else {
        ret += ' +';
      }
      if (k === 'constant') {
        ret += v;
      } else {
        ret += `${v} ${k}`;
      }
    }
    return (ret === '') ? '0' : ret;
  }
}


module.exports = Row;
