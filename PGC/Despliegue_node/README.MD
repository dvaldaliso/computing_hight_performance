# Build image proyect
- docker build -t node-app:1.0 .
# Run
- docker run -d -p 3000:3000 node-app:1.0