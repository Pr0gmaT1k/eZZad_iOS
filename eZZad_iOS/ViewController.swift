//
//  ViewController.swift
//  eZZad_iOS
//
//  Created by AzerTy on 06/03/2017.
//  Copyright © 2017 Pr0gmaT1k. All rights reserved.
//

import UIKit
import MapKit
import GEOSwift

//bbox -1.815,47.3169,-1.6306,47.3932

class ViewController: UIViewController, MKMapViewDelegate {
  //
  // Mark: IBoutlet
  @IBOutlet private weak var mapView: MKMapView!
  
  //
  // Mark: public func
  override func viewDidLoad() {
    super.viewDidLoad()
    setupMap()
    setupDB()
    setupGeoJSON()
  }
  
  func mapView(_ mapView: MKMapView, rendererFor overlay: MKOverlay) -> MKOverlayRenderer {
    switch overlay {
    case let overlay as MKPolygon:
      let polygonRenderer = MKPolygonRenderer(polygon: overlay)
      polygonRenderer.lineWidth = 1
      polygonRenderer.strokeColor = UIColor.black.withAlphaComponent(0.5)
      return polygonRenderer
    case let overlay as MKTileOverlay: return MKTileOverlayRenderer(tileOverlay: overlay)
    default: return MKOverlayRenderer() // empty renderer.
    }
  }
  
  //
  // Mark:- private func
  /** Center map */
  private func setupMap() {
    self.mapView.delegate = self
    let center = CLLocationCoordinate2D(latitude: 47.346471, longitude: -1.720943)
    let viewRegion : MKCoordinateRegion = MKCoordinateRegionMakeWithDistance(center, 4000, 4000);
    let adjustedRegion : MKCoordinateRegion = self.mapView.regionThatFits(viewRegion)
    self.mapView.setRegion(adjustedRegion ,animated:true)
    self.mapView.showsUserLocation = true
  }
  
  /** Load GeoJSON From local file */
  private func setupGeoJSON() {
    if let geoJSONURL = Bundle.main.url(forResource: "AirportPerimeter", withExtension: ".geojson"),
      let geometries = try? Geometry.fromGeoJSON(geoJSONURL),
      let airportPerimeterPolygon = geometries?[0] as? Polygon,
      let airportPerimeterOverlay = airportPerimeterPolygon.mapShape() as? MKPolygon {
      self.mapView.add(airportPerimeterOverlay)
    }
  }
  
  /** Initialise Map DB from MBTiles File. */
  private func setupDB() {
    if let dbPath = Bundle.main.url(forResource: "zad", withExtension: "mbtiles")?.path {
      let overlay = MBtilesOverlay(dbPath: dbPath)
      overlay.canReplaceMapContent = true
      mapView.add(overlay, level: .aboveLabels)
    }
  }
}

