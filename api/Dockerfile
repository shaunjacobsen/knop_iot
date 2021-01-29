FROM node:15.5
RUN mkdir -p /app
WORKDIR /app
COPY ./package.json .
RUN yarn
COPY . .
EXPOSE 3005
CMD yarn run start