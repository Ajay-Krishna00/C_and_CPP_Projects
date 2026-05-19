const fs = require("fs");
const path = require("path");

const PUBLIC_DIR = path.join(__dirname, "public");

function scan(dir) {
    let result = {};

    const items = fs.readdirSync(dir);

    for (const item of items) {
        const fullPath = path.join(dir, item);

        if (fs.statSync(fullPath).isDirectory()) {
            result[item] = scan(fullPath);
        } else {
            result[item] = null;
        }
    }

    return result;
}

const structure = scan(PUBLIC_DIR);

fs.writeFileSync(
    path.join(PUBLIC_DIR, "index.json"),
    JSON.stringify(structure, null, 2)
);

console.log("index.json generated");