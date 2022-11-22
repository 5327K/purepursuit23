import { Point } from "../types/types";

class Api {
  private socket: WebSocket;
  private connected = false;

  private readonly possibleReponses = ["updated-path"];

  public readonly callbacks: {
    [key in typeof this.possibleReponses[number]]: ((
      msg: string
    ) => void)[];
  } = this.possibleReponses.reduce((obj: typeof this.callbacks, key) => {
    obj[key] = [];
    return obj;
  }, {});

  public readonly onopen: ((e: Event) => void)[] = [];

  constructor() {
    this.socket = new WebSocket("ws://localhost:9002");

    this.socket.onopen = (e) => {
      console.log("Connected to socket successfully!");
      this.connected = true;

      for (const callback of this.onopen) callback(e);
    };

    this.socket.onmessage = (msg: MessageEvent<any>) => {
      const tokens = (msg.data as string).split(/\s+/);

      if (tokens[0] === "ERROR") {
        throw new Error(`Something went wrong. Message: "${tokens[1]}"`);
      } else {
        this.handleResponse(tokens[0], msg.data as string);
      }
    };

    this.socket.onerror = (e) => {
      console.error("An unexpected error occured.", e);
    };
  }

  public isConnected = () => {
    return this.connected;
  };

  private handleResponse = (type: string, msg: string) => {
    if (type in this.callbacks) {
      for (const callback of this.callbacks[type]) {
        callback(msg);
      }
    } else {
      throw new Error(`Unrecognized message recieved. Message: ${msg}`);
    }
  };

  public pathUpdated = (
    forwards: boolean,
    maxVel: number,
    maxAccel: number,
    k: number,
    points: Point[]
  ) => {
    this.socket.send(
      `update-path ${forwards ? "1" : "0"} ${maxVel} ${maxAccel} ${k} ${points.length}\n` +
        points.map((pt) => `${pt.x} ${pt.y}`).join("\n")
    );
  };
}

export default Api;
