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
import FBAnnotationClustering

//bbox -1.815,47.3169,-1.6306,47.3932

class ViewController: UIViewController {
  //
  // Mark: IBoutlet
  @IBOutlet fileprivate weak var mapView: MKMapView!
  
  //
  // Mark:- Properties
  fileprivate let clusteringManager = FBClusteringManager()
  
  //
  // Mark: public func
  override func viewDidLoad() {
    super.viewDidLoad()
    setupMap()
    setupDB()
    setupGeoJSON()
  }
  
  override func viewWillAppear(_ animated: Bool) {
    super.viewWillAppear(animated)
    self.refreshAnnotation()
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
    addGeoJSON(bundledFileName: "AirportPerimeter")
    addGeoJSON(bundledFileName:            "Plots")
    addGeoJSON(bundledFileName:           "Places")
    addGeoJSON(bundledFileName:      "RoadsideBar")
  }
  
  /** Initialise Map DB from MBTiles File. */
  private func setupDB() {
    if let dbPath = Bundle.main.url(forResource: "zad", withExtension: "mbtiles")?.path {
      let overlay = MBtilesOverlay(dbPath: dbPath)
      overlay.canReplaceMapContent = true
      mapView.add(overlay, level: .aboveLabels)
    }
  }
  
  /**
   * Add MKOverlay to self.mapView from bundled file
   * :bundledFileName: File name without extension
   */
  private func addGeoJSON(bundledFileName: String) {
    guard let geoJSONURL = Bundle.main.url(forResource: bundledFileName, withExtension: ".geojson"),
      let geometriesO = try? Geometry.fromGeoJSON(geoJSONURL),
      let geometries = geometriesO else { return }
    for geometry in geometries {
      switch geometry {
      case let geometry as Polygon:
        guard let overlay = geometry.mapShape() as? MKOverlay else { break }
        self.mapView.add(overlay)
      case let geometry as MultiPolygon<Polygon>:
        for subGeometry in geometry.geometries {
          guard let overlay = subGeometry.mapShape() as? MKOverlay else { break }
          self.mapView.add(overlay)
        }
      case let geometry as Waypoint:
        let pointAnnotation = PointAnnotation(waypoint: geometry)
        self.clusteringManager.addAnnotations([pointAnnotation])
      default: break
      }
    }
  }
  
  /** Refresh self.mapView Annotation */
  fileprivate func refreshAnnotation() {
    DispatchQueue.global(qos: .userInitiated).async {
      let scale = Double(self.mapView.bounds.size.width) / self.mapView.visibleMapRect.size.width
      let annotationArray = self.clusteringManager.clusteredAnnotations(within: self.mapView.visibleMapRect,
                                                                        withZoomScale:scale)
      DispatchQueue.main.async {
        self.clusteringManager.displayAnnotations(annotationArray,
                                                  on: self.mapView)
      }
    }
  }
}

// Mark:- MKMapViewDelegate
extension ViewController: MKMapViewDelegate {
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
  
  func mapView(_ mapView: MKMapView, regionDidChangeAnimated animated: Bool) {
    self.refreshAnnotation()
  }
  
  func mapView(_ mapView: MKMapView, viewFor annotation: MKAnnotation) -> MKAnnotationView? {
    switch annotation {
    case let annotation as FBAnnotationCluster:
      let clusterView = ClusterView.loadFromNib()
      clusterView.annotationCount = annotation.annotations.count
      return clusterView
    case let annotation as PointAnnotation:
      let annotationView = AnnotationView.loadFromNib()
      annotationView.setup(pointAnnotation: annotation)
      return annotationView
    default:
      return nil
    }
  }
}
