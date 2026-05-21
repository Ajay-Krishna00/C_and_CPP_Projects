# C_and_CPP_Projects
## ⚝Welcome to my C and C++ Projects repository!😎

This repository showcases various projects, exercises, and experiments I've worked on to improve my skills in C and C++. Feel free to explore, learn, and use them as inspiration for your own projects.

## Usage

- Clone the repository using git clone
- Explore the folders and files to find something interesting!
- Compile and run the projects using a C or C++ compiler (e.g., gcc or clang++)

## API

This repo is deployed on Vercel and exposes a `/ask` endpoint that forwards to Gemini.

### Setup

- Add a `GEMINI_API_KEY` environment variable in Vercel.

### Example

```bash
curl -X POST "https://c-and-cpp-projects.vercel.app/ask" \
	-H "Content-Type: application/json" \
	-d "{\"code\":\"int main(){return 0;}\",\"question\":\"What does this do?\"}"
```

## Contributing

- Feel free to submit pull requests with new projects, exercises, or examples!
- Open an issue to report any bugs or suggest new ideas.

## License

This repository is licensed under the MIT License.

## Author

Ajay Krishna D
- Email: enthusiastajay00@gmail.com
