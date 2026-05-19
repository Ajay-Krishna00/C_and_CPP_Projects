const fs = require("fs");
const path = require("path");

module.exports = async (req, res) => {
    try {
        const publicDir = path.join(__dirname, "..", "public");

        function scan(dir) {
            const result = {};
            const items = fs.readdirSync(dir);
            for (const item of items) {
                const fullPath = path.join(dir, item);
                if (fs.statSync(fullPath).isDirectory()) {
                    result[item] = scan(fullPath);
                } else {
                    result[item] = "file";
                }
            }
            return result;
        }
        const structure = scan(publicDir);
        res.setHeader("Content-Type", "application/json");
        res.status(200).json(structure);
    } catch (err) {
        res.status(500).json({
            error: err.message
        });
    }
};