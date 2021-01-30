import * as express from 'express';

export default function respond_event(
  req: express.Request,
  res: express.Response,
  next: express.NextFunction,
) {
  const { type, device_id } = req.params;
  if (type === 'button_push') {
    return res.json({ response: 'Button pushed!', device_id });
  }
  return res.json({ response: 'Hello, world' });
}
