const fs = require('fs');
const path = require('path');

module.exports = (req, res) => {
  const basePath = path.join(process.cwd(), "public");

  function scan(dir) {
    const results = [];
    const items = fs.readdirSync(dir);
    items.forEach(item => {
      const fullPath = path.join(dir, item);
      if (fs.statSync(fullPath).isDirectory()) {
          result[item] = scan(fullPath);
      } else {
          result[item] = "file";
      }
    })
  }
  const files = scan(basePath);
  res.setHeader('Content-Type', 'application/json');
  res.status(200).json(files);
}