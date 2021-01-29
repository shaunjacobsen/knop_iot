FROM node:15.5
RUN mkdir -p /app
WORKDIR /app
COPY ./package.json .
COPY ./yarn.lock .
RUN yarn
COPY . .
EXPOSE 3005
CMD yarn run start